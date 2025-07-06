@echo off
if not exist "../bin/task_manager.exe" (
    echo Executable not found. Please build the app first.
    pause
    exit /b
)

"../bin/task_manager.exe"
pause