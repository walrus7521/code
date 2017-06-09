

# https://ss64.com/ps/syntax-hash-tables.html

[int[]] $myArray = @()

for ($i=0; $i -lt 4; $i++) {
    $myArray += $i
    Write-Host "i = " + $myArray[$i] -ForegroundColor Magenta    
}

Write-Host "length = " + $myArray.length -ForegroundColor Blue    

for ($i=0; $i -lt $myArray.length; $i++) {
    Write-Host "i = " + $myArray[$i] -ForegroundColor Yellow    
}
