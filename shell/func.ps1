function Write-PI{
    param (
        [double]$round = 2
    )
    $PI = 3.1415926
    
    $round_PI = [Math]::Round($PI, $round)
    Write-Host "PI = $round_PI"
}


Write-PI