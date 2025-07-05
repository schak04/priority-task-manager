@echo off
if not exist task_manager.exe (
    echo Executable not found. Please build the project first.
    pause
    exit /b
)
task_manager.exe
pause