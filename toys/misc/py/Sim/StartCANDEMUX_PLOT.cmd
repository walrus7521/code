@ECHO OFF
setlocal EnableDelayedExpansion

REM First, kill MX App or other CAN_DEMUX apps
call kill_CAN.cmd

cd CAN_DEMUX
start /MIN Debug/CANDEMUX.exe -k -m -r -z -c -T -t -u

ping 127.0.0.1 -n 6 -w 123 >nul
:start
del /F plotfilename.txt
dir *flt_data_A_All.csv  /b /OD | tail -n1 > plotfilename.txt
set /p fplotname= <plotfilename.txt
echo %fplotname%
tail -f %fplotname% | python3 plot_pipe77.py -t actuator_commands_roll:0 -c actuator_commands_roll,actuator_positions_roll,actuator_mvc_roll -l 200 -p 10
rem tail -f %fplotname% | python3 plot_pipe77.py -t actuator_commands_roll:0 -c actuator_mvc_roll -l 200 -p 10
goto start

REM Should never get here
REM
