terraform {
  required_providers {
    azurerm = {
      source  = "hashicorp/azurerm"
      version = "~>3.0"
    }
  }
}

provider "azurerm" {
  subscription_id = "9436d3ab-8e63-47f4-9e00-b5243817c21a"
  tenant_id = "b0f6b059-72f0-45d3-aa20-48724019cb34"
  client_id = "26023955-62af-4826-a10e-66779d680386"
  client_secret = "Bsz8Q~Cq4kL01fQ1GQhvRI0GIWD5KFREccY8yaCL"

  features {}
}