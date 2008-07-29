@echo off
:: WARNING This script only works with directories withouth spaces!

:: Settings
set srcDir=..\src
set sleepCmd=sleep.exe 100


:: Copy all library headers if no argument is given
if [%1]==[] (GOTO :ALLLIBS) else (GOTO :ONELIB)
GOTO :DONE


:ALLLIBS
:: Copy the headers of all available libraries
echo No arguments given. Copying all header files from %srcDir%
echo.
pushd .
cd %srcDir%
for /D %%D in (*.*) do popd & CALL :ONELIB %%D & echo.
GOTO :DONE


:ONELIB
:: Copy the headers of one library
echo Rebuilding the %1 header files...
if exist %1 del /Q %1\*.*
%sleepCmd%
if not exist %1 md %1
for /r "%srcDir%\%1" %%F in (*.h) do copy "%%F" "%1\" > nul
for /r "%srcDir%\%1" %%F in (*.inl) do copy "%%F" "%1\" > nul
for /r "%srcDir%\%1" %%F in (*.mcr) do copy "%%F" "%1\" > nul
GOTO :eof



:DONE
