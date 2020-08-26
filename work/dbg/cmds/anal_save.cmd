REM https://achindrabhatnagar.wordpress.com/2009/06/04/command-line-automation-of-memory-dump-analysis/
REM https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/kd-command-line-options
REM https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/using-script-files

rem "\Program Files (x86)\Windows Kits\10\Debuggers\x64\kd.exe" -z "WATCHDOG-20200616-0213.dmp"
rem "\Program Files (x86)\Windows Kits\10\Debuggers\x64\kd.exe" -z "WATCHDOG-20200616-0213.dmp" -c "!analyze -v; q" > dumper.log
rem "\Program Files (x86)\Windows Kits\10\Debuggers\x64\kd.exe" -z "WATCHDOG-20200616-0213.dmp" -c "$< thrd.kd; q" > dumper.log
rem
rem "\Program Files (x86)\Windows Kits\10\Debuggers\x64\kd.exe" -z "WATCHDOG-20200616-0213.dmp" -logo "the_dude.log" -c "$$< .\thrd.kd"
"\Program Files (x86)\Windows Kits\10\Debuggers\x64\kd.exe" -z "WATCHDOG-20200616-0213.dmp" -c "$$< .\thrd.kd"

