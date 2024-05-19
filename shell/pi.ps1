param (
    [Parameter(position= 1,Mandatory = $true)]
    [double]$PI,

    [Parameter(position = 0)]
    [string]$str
)
Write-Host "PI = $PI"
Write-Host "str = $str"
