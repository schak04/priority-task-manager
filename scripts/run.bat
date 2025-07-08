@echo off
REM Get the folder where this script is located
set SCRIPT_DIR=%~dp0

REM Normalize path (remove trailing backslash if present)
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Compute full path to the executable
set EXE_PATH=%SCRIPT_DIR%\..\bin\task_manager.exe

REM Check if executable exists
if not exist "%EXE_PATH%" (
    echo Executable not found. Please build the app first.
    pause
    exit /b
)

REM Run the app
"%EXE_PATH%"
pause