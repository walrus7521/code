@echo off

setlocal enabledelayedexpansion
rem title=authorized hacker

rem Create vector with names of days

set i=0
for %%d in (Sunday Monday Tuesday Wednesday Thrusday Friday Saturday) do (
   set /A i=i+1
   set day[!i!]=%%d
   REM echo %%d
)


set quotes[0]=authorized hacker
set quotes[1]=arrest this man
set quotes[2]=vulnerable
set quotes[3]=victim
set quotes[4]=dialup
set quotes[5]=compromise
set quotes[6]=aethernet
set quotes[7]=insecure

set /a num=%random% %%7
REM echo %num%
REM echo !quotes[%num%]!
REM title !quotes[%num%]!

doskey ise=powershell_ise
doskey dev=cd /d %SystemDrive%\git
doskey rtos=cd /d %SystemDrive%\sandbox\rtos\FreeRTOSv10.3.1\FreeRTOSv10.3.1\FreeRTOS\Demo\WIN32-MSVC
doskey jaz=cd /d %SystemDrive%\git\Jaz-SAM
doskey zap=cd /d %SystemDrive%\git\mcu
doskey skip=cd /d %SystemDrive%\git\mcu\src\projects\zap\skip-b
doskey avila=cd /d %SystemDrive%\git\avila-sam
doskey paloma=cd /d %SystemDrive%\git\paloma-sam
doskey haven=cd /d %SystemDrive%\git\havenu-sam
doskey cambria=cd /d %SystemDrive%\git\cambria-sam
doskey cruz=cd /d %SystemDrive%\git\cruz-sam
doskey fox=cd /d %SystemDrive%\git\foxburg-sam
doskey jupiter=cd /d %SystemDrive%\git\mcu-ple
doskey gas=cd /d %SystemDrive%\git\GasGauge\SP4_GasGaugeTelemetryDecoder
doskey sand=cd /d %SystemDrive%\sandbox
doskey grok=cd /d C:\sandbox\code\toys\grokkage
doskey home=cd /d %USERPROFILE%
doskey pur=del *~
doskey cat=type $*
doskey ll=dir $*
doskey l=dir $*
doskey ls=dir $*
doskey cp=xcopy $*
doskey mv=move $*
doskey rm=del $*
doskey grep=findstr $*
doskey alias=doskey /macros

@echo on

