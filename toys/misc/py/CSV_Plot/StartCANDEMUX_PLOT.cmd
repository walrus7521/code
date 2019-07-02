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
REM tail -f %fplotname% | plot_pipe77.py
tail -f %fplotname% | python3 plot_pipe77.py -t raw_rates_0_Z -v 4 -c raw_rates_0_X,raw_rates_0_Y,raw_rates_0_Z

goto start

REM Should never get here
REM
