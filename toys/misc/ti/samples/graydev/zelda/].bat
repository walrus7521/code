@echo off

tasm -t80 -b -i zelda.z80 zelda.bin
if errorlevel 1 goto ERR
devpac83 zelda
echo.
del zelda.list
del zelda.bin

md backups
cd backups
md prev
cd prev
md prev
cd..
cd..

copy backups\prev\*.* backups\prev\prev\

copy *.* backups\prev\

echo.
echo === nice work ===
echo.

goto XIT

:ERR
echo.
echo Hey, something is wrong here!
echo.
:XIT
