@echo off
REM Get the directory where this script is located
set SCRIPT_DIR=%~dp0

REM Normalize path (remove trailing \)
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Define absolute paths
set BUILD_DIR=%SCRIPT_DIR%\..\build
set BIN_DIR=%SCRIPT_DIR%\..\bin
set DATA_DIR=%SCRIPT_DIR%\..\data
set SRC_DIR=%SCRIPT_DIR%\..\src
set LIB_DIR=%SCRIPT_DIR%\..\lib

REM Create required directories if they don't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"
if not exist "%DATA_DIR%" mkdir "%DATA_DIR%"

echo Compiling SQLite source...
gcc -c "%LIB_DIR%\sqlite3.c" -o "%BUILD_DIR%\sqlite3.o" -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION

echo Compiling C++ source...
g++ -c "%SRC_DIR%\task_manager.cpp" -o "%BUILD_DIR%\task_manager.o"

echo Linking both to create standalone executable...
g++ "%BUILD_DIR%\task_manager.o" "%BUILD_DIR%\sqlite3.o" -o "%BIN_DIR%\task_manager.exe" -static -static-libgcc -static-libstdc++

echo.
echo Build complete. Run with: scripts\run.bat
pause