@echo off
setlocal

set "CC=g++"
set "CPPFLAGS=-std=c++11 -Wall -g -Iinclude"
set "SRCS=src/main.cpp src/blockEntity.cpp src/movableEntity.cpp src/hollow.cpp"
set "SRCS_TST=tests/main_test.cpp src/blockEntity.cpp src/movableEntity.cpp src/hollow.cpp"

if "%1"=="" goto game
if "%1"=="game" goto game
if "%1"=="game_test" goto game_test
if "%1"=="clean" goto clean

echo Invalid target: %1
exit /b 1

:game
echo Building game...
%CC% %CPPFLAGS% %SRCS% -o game.exe
if %errorlevel% neq 0 exit /b %errorlevel%
echo Build successful: game.exe
exit /b 0

:game_test
echo Building game_test...
%CC% %CPPFLAGS% %SRCS_TST% -o game_test.exe
if %errorlevel% neq 0 exit /b %errorlevel%
echo Build successful: game_test.exe
exit /b 0

:clean
echo Cleaning...
if exist game.exe del game.exe
if exist game_test.exe del game_test.exe
if exist src\*.o del src\*.o
if exist src\*.d del src\*.d
if exist tests\*.o del tests\*.o
if exist tests\*.d del tests\*.d
echo Clean successful.
exit /b 0
