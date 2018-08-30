@echo off
setlocal enabledelayedexpansion

title=authorized hacker

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
title !quotes[%num%]!

doskey dev=cd /d %SystemDrive%\data
doskey fdev=cd /d F:\data
doskey code=cd /d %SystemDrive%\code
doskey prj=cd /d %SystemDrive%\data\Projects
doskey ddk=cd /d %SystemDrive%\\WinDDK\7600.16385.1
doskey repo=cd /d %SystemDrive%\code
doskey home=cd /d %USERPROFILE%
doskey share=cd /d %HOMEDRIVE%%HOMEPATH%
doskey pur=del *~
doskey ll=dir $*
doskey l=dir $*
doskey ls=dir $*
doskey cp=xcopy $*
doskey mv=move $*
doskey rm=del $*
doskey grep=findstr $*
doskey alias=doskey /macros

@echo on
