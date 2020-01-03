rem @echo off
rem powershell -ExecutionPolicy Bypass -Command Install-SurfacePackage -ConfigPath .\Packages.config %*
echo %~dp0
rem set PATH=%~dp0.tools;%PATH%
