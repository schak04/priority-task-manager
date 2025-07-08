@echo off
REM Get the directory this script is located
set SCRIPT_DIR=%~dp0

REM Normalize path (remove trailing \)
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

echo Compiling SQLite source...
gcc -c "%SCRIPT_DIR%\..\lib\sqlite3.c" -o "%SCRIPT_DIR%\..\build\sqlite3.o"

echo Compiling C++ source...
g++ -c "%SCRIPT_DIR%\..\src\task_manager.cpp" -o "%SCRIPT_DIR%\..\build\task_manager.o"

echo Linking both to create executable...
g++ "%SCRIPT_DIR%\..\build\task_manager.o" "%SCRIPT_DIR%\..\build\sqlite3.o" -o "%SCRIPT_DIR%\..\bin\task_manager.exe" -static

echo.
echo Build complete. Run with: scripts\run.bat
pause