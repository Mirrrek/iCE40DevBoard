@echo off

set COLOR_RED=[31m
set COLOR_GREEN=[32m
set COLOR_BOLD=[1m
set COLOR_RESET=[0m

set PORT=COM3
if [%1] neq [] set PORT=%1

arduino-cli compile --fqbn arduino:avr:uno src
if ERRORLEVEL 1 echo %COLOR_BOLD%%COLOR_RED%Compilation failed, aborting build.%COLOR_RESET% && exit
arduino-cli upload -p %PORT% --fqbn arduino:avr:uno src
if ERRORLEVEL 1 echo %COLOR_BOLD%%COLOR_RED%Upload failed, aborting build.%COLOR_RESET% && exit
echo %COLOR_BOLD%%COLOR_GREEN%Build succeeded.%COLOR_RESET%
arduino-cli monitor -p %PORT%
