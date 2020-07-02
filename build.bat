@echo off
cls

echo ==================
echo === JUGGERNAUT ===
echo ==================
echo.
echo Select you Visual Studio version:
echo     1. Visual Studio 2015
echo     2. Visual Studio 2017
echo     3. Visual Studio 2019

echo.
set /p version=Type Version: 

if not exist "./build" mkdir "./build"
cd build

if "%version%" == "1" goto vs2015
if "%version%" == "2015" goto vs2015

if "%version%" == "2" goto vs2017
if "%version%" == "2017" goto vs2017

if "%version%" == "3" goto vs2019
if "%version%" == "2019" goto vs2019

:vs2015
echo VS 2015
cmake .. -G "Visual Studio 14 2015" -A x64
goto end

:vs2017
echo VS 2017
cmake .. -G "Visual Studio 15 2017" -A x64
goto end

:vs2019
echo VS 2019
cmake .. -G "Visual Studio 16 2019" -A x64
goto end

:end

echo.
pause
