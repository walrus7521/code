@ECHO OFF
setlocal EnableDelayedExpansion

:start

rem echo dude
tail -f data.csv | python3 plot_pipe77.py -f capture.ini

rem goto start

REM Should never get here
REM

