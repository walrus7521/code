
param (
    [string]$server = "http://defaultserver",
    [Parameter(Mandatory=$true)][string]$username,
    [string]$password = $( Read-Host "Input password, please" )
)

write-output $server
write-output $username
write-output $password

