#Mount the EFI partition
mountvol s: /s
S:

# Backup the BCD
cd EFI\Microsoft\Boot
copy BCD BCD.bak

# setup KD USB
bcdedit /store BCD /set {default} debug on
bcdedit /store BCD /set {default} bootdebug on
bcdedit /store BCD /set {bootmgr} bootdebug on
bcdedit /store BCD /dbgsettings USB targetname:ttt
	
# verify
bcdedit /store BCD /dbgsettings

