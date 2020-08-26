# setup KD USB
bcdedit /dbgsettings USB targetname:ttt
bcdedit /set "{dbgsettings}" busparams 0.20.0
bcdedit /debug on
bcdedit /bootdebug "{bootmgr}" on

#winresume.efi
bcdedit /bootdebug "{77ff01e8-a675-11e8-a686-5882a88da84e}" on
#bcdedit /enum all

@rem Disabling USB selective suspend:
powercfg /SETDCVALUEINDEX SCHEME_CURRENT 2a737441-1930-4402-8d77-b2bebba308a3 48e6b7a6-50f5-4782-a5d4-53bb8f07e226 0
powercfg /SETACVALUEINDEX SCHEME_CURRENT 2a737441-1930-4402-8d77-b2bebba308a3 48e6b7a6-50f5-4782-a5d4-53bb8f07e226 0
	
# verify
bcdedit /dbgsettings

