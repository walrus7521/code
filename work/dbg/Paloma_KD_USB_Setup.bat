@rem setup KD USB for Paloma
bcdedit /set debug on
bcdedit /dbgsettings usb targetname:ttt
bcdedit /set "{dbgsettings}" busparams 3.0.3

@rem bcdedit /bootdebug "{bootmgr}" on

@rem verify
@rem bcdedit /enum all
bcdedit /dbgsettings
pause

@rem reboot
shutdown -r -t 0
