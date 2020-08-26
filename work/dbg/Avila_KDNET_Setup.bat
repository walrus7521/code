@rem setup KDNET fro Avila
bcdedit /set debug on
bcdedit /dbgsettings usb targetname:ttt
bcdedit.exe /dbgsettings net hostip:169.254.255.255 port:50001 key:1.2.3.4 
bcdedit /set "{dbgsettings}" busparams 0.20.0
bcdedit.exe /set "{dbgsettings}" dhcp false

@rem For 19h1 Windows :
bcdedit.exe /set "{globalsettings}" loadoptions EEM

@rem For debugging bootmgr/winload/hv:
bcdedit.exe /set "{globalsettings}" testsigning true

@rem bcdedit /bootdebug "{bootmgr}" on

@rem verify
@rem bcdedit /enum all
bcdedit /dbgsettings
pause

@rem reboot
shutdown -r -t 0
