@echo off
:: This script can be used to easily create a new NVE2 project

:: Settings
set buildenvDir=.
set srcDir=..\..\src
set templateDir=templates
set /P projectName=Name of the project (Note: plugins should end with Plugin): 
set arch=1
set /P projectType=Type of project (1=library; 2=executable; 3=qt application; 4=qt library; 5=plugin): 

echo.


:: Check if the project already exists
echo Checking if "%buildenvDir%\%projectName%.vcproj" already exists...
if exist "%buildenvDir%\%projectName%.vcproj" GOTO :PROJEXISTS
echo   OK. It doesn't exist yet.
echo.

if %arch%==1 set templateDir=%templateDir%\win32
if %arch%==2 set templateDir=%templateDir%\wm2005
if %arch%==3 set templateDir=%templateDir%\win32+wm2005

if %projectType%==1 set templateDir=%templateDir%\dll
if %projectType%==2 set templateDir=%templateDir%\app
if %projectType%==3 set templateDir=%templateDir%\qtapp
if %projectType%==4 set templateDir=%templateDir%\qtlib
if %projectType%==5 set templateDir=%templateDir%\plugin


:: Check if the combination exists
echo Checking if there is a template in %templateDir%...
if not exist %templateDir% GOTO :NOTEMPLATE
echo   OK. The template exists.
echo.


echo Creating the project '%projectName%'...

echo Checking if %srcDir%\%projectName% already exists...
if exist %srcDir%\%projectName% GOTO :CREATEPROJ

:: Create the directory
echo   Creating the directory %srcDir%\%projectName%...
mkdir "%srcDir%\%projectName%"

:: Copy all source files
echo   Copying the template source files...
copy "%templateDir%\*.h" "%srcDir%\%projectName%" > nul
copy "%templateDir%\*.cpp" "%srcDir%\%projectName%" > nul


:CREATEPROJ
:: Copy the project file
echo   Creating the project file...
copy "%templateDir%\ProjectName.vcproj" "%buildenvDir%\%projectName%.vcproj" > nul

echo.
echo Done!
echo.
echo Now, in %buildenvDir%\%projectName%.vcproj, you have to search-and-replace
echo PROJECTNAME (case sensitive) with the name of your project in capitals,
echo add %buildenvDir%\%projectName%.vcproj to your solution,
echo and add all files of %srcDir%\%projectName% to your project.
echo You'll have to do the same search-and-replace as above in global.h
echo.
echo Good luck!
pause
GOTO :eof


:PROJEXISTS
echo A project with this name already exists! Try again with a new name.
pause
GOTO :eof

:NOTEMPLATE
echo We don't have a template yet for this project and architecture combination.
echo Go ahead and make one!
pause
GOTO :eof
