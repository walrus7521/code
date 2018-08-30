@echo off
setlocal enabledelayedexpansion

REM ###### Set this to be the currently active project
set PROJECT=HdgHold
set OPENCV_DIR=c:\opencv\opencv31\build
echo Your project is set to: %PROJECT%
REM ###### Set this to be the currently active project

rem if "%1" == "" goto NoPrj
    rem ## note $T is used to separate multiple commands per line --> see doskey /?
    rem set PROJECT=%1
    doskey cunit=cd /d %SystemDrive%\helitrak\%PROJECT%\SWDev\Test\Model\Outer_Loop\Roll_Target_Gen $T title cunit
    doskey munit=cd /d %SystemDrive%\helitrak\%PROJECT%\SimModel\Test\CLaw\ADP\OuterLoop\OL_RollTargetGen2_unitTest $T title munit
    doskey code=cd /d %SystemDrive%\helitrak\%PROJECT%\SWDev\Model\Outer_Loop\Source $T title code
    doskey tools=cd /d %SystemDrive%\helitrak\%PROJECT%\SWDev\Tools\In_Flight_Tools $T title tools
:NoPrj

title=authorized hacker
rem Create vector with names of days
set i=0
for %%d in (Sunday Monday Tuesday Wednesday Thrusday Friday Saturday) do (
   set /A i=i+1
   set day[!i!]=%%d
   REM echo %%d
)

set quotes[0]=authorized hacker
set quotes[1]=detain this man
set quotes[2]=exploit that vulnerability
set quotes[3]=volunteer
set quotes[4]=dialup
set quotes[5]=no compromise
set quotes[6]=aethernet
set quotes[7]=secure

set /a num=%random% %%7
REM echo %num%
REM echo !quotes[%num%]!
title !quotes[%num%]!

doskey sched=cd /d m:\code\schedule
doskey dev=cd /d %SystemDrive%\helitrak
doskey fdev=cd /d F:\helitrak
doskey hack=cd /d %SystemDrive%\code $T title hack
doskey hack2=cd /d %SystemDrive%\code2 $T title hackit
doskey prj=cd /d %SystemDrive%\helitrak\Projects
doskey ddk=cd /d %SystemDrive%\\WinDDK\7600.16385.1
doskey repo=cd /d %SystemDrive%\code
doskey home=cd /d %USERPROFILE%
doskey share=cd /d %HOMEDRIVE%%HOMEPATH%
doskey cpd=cd /d H:\helitrak\CPD
doskey pur=del *~
doskey ll=dir $*
doskey l=dir $*
doskey ls=dir $*
doskey cp=xcopy $*
doskey mv=move $*
doskey rm=del $*
doskey grep=findstr $*
doskey alias=doskey /macros
doskey g14=g++ -std=c++0x $*
doskey boss=cd /d C:\helitrak\CPD1_CERT\Tools\VideoProcessing\VideoReview $T cls $T vi VideoReview\VideoReview.cpp

@echo on
