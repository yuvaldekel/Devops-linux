//go:build go1.18
// +build go1.18

package azuread

import (
	"context"
	"crypto"
	"crypto/x509"
	"errors"
	"fmt"
	"os"
	"strings"

	"github.com/Azure/azure-sdk-for-go/sdk/azcore"
	"github.com/Azure/azure-sdk-for-go/sdk/azcore/cloud"
	"github.com/Azure/azure-sdk-for-go/sdk/azcore/policy"
	"github.com/Azure/azure-sdk-for-go/sdk/azidentity"
	mssql "github.com/microsoft/go-mssqldb"
	"github.com/microsoft/go-mssqldb/msdsn"
)

const (
	ActiveDirectoryDefault     = "ActiveDirectoryDefault"
	ActiveDirectoryIntegrated  = "ActiveDirectoryIntegrated"
	ActiveDirectoryPassword    = "ActiveDirectoryPassword"
	ActiveDirectoryInteractive = "ActiveDirectoryInteractive"
	// ActiveDirectoryMSI is a synonym for ActiveDirectoryManagedIdentity
	ActiveDirectoryMSI             = "ActiveDirectoryMSI"
	ActiveDirectoryManagedIdentity = "ActiveDirectoryManagedIdentity"
	// ActiveDirectoryApplication is a synonym for ActiveDirectoryServicePrincipal
	ActiveDirectoryApplication                 = "ActiveDirectoryApplication"
	ActiveDirectoryServicePrincipal            = "ActiveDirectoryServicePrincipal"
	ActiveDirectoryServicePrincipalAccessToken = "ActiveDirectoryServicePrincipalAccessToken"
	ActiveDirectoryDeviceCode                  = "ActiveDirectoryDeviceCode"
	ActiveDirectoryAzCli                       = "ActiveDirectoryAzCli"
	scopeDefaultSuffix                         = "/.default"
)

type azureFedAuthConfig struct {
	adalWorkflow byte
	mssqlConfig  msdsn.Config
	// The detected federated authentication library
	fedAuthLibrary  int
	fedAuthWorkflow string
	// Service principal logins
	clientID        string
	tenantID        string
	clientSecret    string
	certificatePath string
	resourceID      string

	// AD password/managed identity/interactive
	user                string
	password            string
	applicationClientID string
}

// parse returns a config based on an msdsn-style connection string
func parse(dsn string) (*azureFedAuthConfig, error) {
	mssqlConfig, err := msdsn.Parse(dsn)
	if err != nil {
		return nil, err
	}
	config := &azureFedAuthConfig{
		fedAuthLibrary: mssql.FedAuthLibraryReserved,
		mssqlConfig:    mssqlConfig,
	}

	err = config.validateParameters(mssqlConfig.Parameters)
	if err != nil {
		return nil, err
	}

	return config, nil
}

func (p *azureFedAuthConfig) validateParameters(params map[string]string) error {

	fedAuthWorkflow := params["fedauth"]
	if fedAuthWorkflow == "" {
		return nil
	}

	p.fedAuthLibrary = mssql.FedAuthLibraryADAL

	p.applicationClientID = params["applicationclientid"]

	switch {
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryPassword):
		if p.applicationClientID == "" {
			return errors.New("applicationclientid parameter is required for " + ActiveDirectoryPassword)
		}
		p.adalWorkflow = mssql.FedAuthADALWorkflowPassword
		p.user = params["user id"]
		p.password = params["password"]
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryIntegrated):
		// Active Directory Integrated authentication is not fully supported:
		// you can only use this by also implementing an a token provider
		// and supplying it via ActiveDirectoryTokenProvider in the Connection.
		p.adalWorkflow = mssql.FedAuthADALWorkflowIntegrated
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryManagedIdentity) || strings.EqualFold(fedAuthWorkflow, ActiveDirectoryMSI):
		// When using MSI, to request a specific client ID or user-assigned identity,
		// provide the ID in the "user id" parameter
		p.adalWorkflow = mssql.FedAuthADALWorkflowMSI
		p.resourceID = params["resource id"]
		p.clientID, _ = splitTenantAndClientID(params["user id"])
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryApplication) || strings.EqualFold(fedAuthWorkflow, ActiveDirectoryServicePrincipal):
		p.adalWorkflow = mssql.FedAuthADALWorkflowPassword
		// Split the clientID@tenantID format
		// If no tenant is provided we'll use the one from the server
		p.clientID, p.tenantID = splitTenantAndClientID(params["user id"])
		if p.clientID == "" {
			return errors.New("Must provide 'client id[@tenant id]' as username parameter when using ActiveDirectoryApplication authentication")
		}

		p.clientSecret = params["password"]

		p.certificatePath = params["clientcertpath"]

		if p.certificatePath == "" && p.clientSecret == "" {
			return errors.New("Must provide 'password' parameter when using ActiveDirectoryApplication authentication without cert/key credentials")
		}
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryDefault) || strings.EqualFold(fedAuthWorkflow, ActiveDirectoryAzCli) || strings.EqualFold(fedAuthWorkflow, ActiveDirectoryDeviceCode):
		p.adalWorkflow = mssql.FedAuthADALWorkflowPassword
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryInteractive):
		if p.applicationClientID == "" {
			return errors.New("applicationclientid parameter is required for " + ActiveDirectoryInteractive)
		}
		// user is an optional login hint
		p.user = params["user id"]
		// we don't really have a password but we need to use some value.
		p.adalWorkflow = mssql.FedAuthADALWorkflowPassword
	case strings.EqualFold(fedAuthWorkflow, ActiveDirectoryServicePrincipalAccessToken):
		p.fedAuthLibrary = mssql.FedAuthLibrarySecurityToken
		p.adalWorkflow = mssql.FedAuthADALWorkflowNone
		p.password = params["password"]

		if p.password == "" {
			return errors.New("Must provide 'password' parameter when using ActiveDirectoryServicePrincipalAccessToken authentication")
		}
	default:
		return fmt.Errorf("Invalid federated authentication type '%s': expected one of %+v",
			fedAuthWorkflow,
			[]string{ActiveDirectoryApplication, ActiveDirectoryServicePrincipal, ActiveDirectoryDefault, ActiveDirectoryIntegrated, ActiveDirectoryInteractive, ActiveDirectoryManagedIdentity, ActiveDirectoryMSI, ActiveDirectoryPassword, ActiveDirectoryAzCli, ActiveDirectoryDeviceCode})
	}
	p.fedAuthWorkflow = fedAuthWorkflow
	return nil
}

func splitTenantAndClientID(user string) (string, string) {
	// Split the user name into client id and tenant id at the @ symbol
	at := strings.IndexRune(user, '@')
	if at < 1 || at >= (len(user)-1) {
		return user, ""
	}

	return user[0:at], user[at+1:]
}

func splitAuthorityAndTenant(authorityURL string) (string, string) {
	separatorIndex := strings.LastIndex(authorityURL, "/")
	tenant := authorityURL[separatorIndex+1:]
	authority := authorityURL[:separatorIndex]
	return authority, tenant
}

func (p *azureFedAuthConfig) provideActiveDirectoryToken(ctx context.Context, serverSPN, stsURL string) (string, error) {
	var cred azcore.TokenCredential
	var err error
	authority, tenant := splitAuthorityAndTenant(stsURL)
	// client secret connection strings may override the server tenant
	if p.tenantID != "" {
		tenant = p.tenantID
	}
	scope := serverSPN
	if !strings.HasSuffix(serverSPN, scopeDefaultSuffix) {
		scope = serverSPN + scopeDefaultSuffix
	}

	switch p.fedAuthWorkflow {
	case ActiveDirectoryServicePrincipal, ActiveDirectoryApplication:
		switch {
		case p.certificatePath != "":
			var certData []byte
			certData, err = os.ReadFile(p.certificatePath)
			if err == nil {
				var certs []*x509.Certificate
				var key crypto.PrivateKey
				certs, key, err = azidentity.ParseCertificates(certData, []byte(p.clientSecret))
				if err == nil {
					cred, err = azidentity.NewClientCertificateCredential(tenant, p.clientID, certs, key, nil)
				}
			}
		default:
			cred, err = azidentity.NewClientSecretCredential(tenant, p.clientID, p.clientSecret, nil)
		}
	case ActiveDirectoryServicePrincipalAccessToken:
		return p.password, nil
	case ActiveDirectoryPassword:
		cred, err = azidentity.NewUsernamePasswordCredential(tenant, p.applicationClientID, p.user, p.password, nil)
	case ActiveDirectoryMSI, ActiveDirectoryManagedIdentity:
		if p.resourceID != "" {
			cred, err = azidentity.NewManagedIdentityCredential(&azidentity.ManagedIdentityCredentialOptions{ID: azidentity.ResourceID(p.resourceID)})
		} else if p.clientID != "" {
			cred, err = azidentity.NewManagedIdentityCredential(&azidentity.ManagedIdentityCredentialOptions{ID: azidentity.ClientID(p.clientID)})
		} else {
			cred, err = azidentity.NewManagedIdentityCredential(nil)
		}
	case ActiveDirectoryInteractive:
		c := cloud.Configuration{ActiveDirectoryAuthorityHost: authority}
		config := azcore.ClientOptions{Cloud: c}
		cred, err = azidentity.NewInteractiveBrowserCredential(&azidentity.InteractiveBrowserCredentialOptions{ClientOptions: config, ClientID: p.applicationClientID})

	case ActiveDirectoryDeviceCode:
		cred, err = azidentity.NewDeviceCodeCredential(&azidentity.DeviceCodeCredentialOptions{ClientID: p.applicationClientID})
	case ActiveDirectoryAzCli:
		cred, err = azidentity.NewAzureCLICredential(&azidentity.AzureCLICredentialOptions{TenantID: p.tenantID})
	default:
		// Integrated just uses Default until azidentity adds Windows-specific authentication
		cred, err = azidentity.NewDefaultAzureCredential(nil)
	}

	if err != nil {
		return "", err
	}
	opts := policy.TokenRequestOptions{Scopes: []string{scope}}
	tk, err := cred.GetToken(ctx, opts)
	if err != nil {
		return "", err
	}
	return tk.Token, err
}
