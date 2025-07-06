@echo off
REM Build SQLite C file with C compiler
gcc -c sqlite3.c -o sqlite3.o

REM Build C++ file
g++ -c task_manager.cpp -o task_manager.o

REM Link both to create executable
g++ task_manager.o sqlite3.o -o task_manager.exe -static

echo.
echo Build complete. Run it with: run.bat
pause
