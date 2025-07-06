@echo off
echo Compiling SQLite source...
gcc -c sqlite3.c -o sqlite3.o

echo Compiling C++ source...
g++ -c task_manager.cpp -o task_manager.o

echo Linking both to create executable...
g++ task_manager.o sqlite3.o -o task_manager.exe -static

echo.
echo Build complete. Run it with: run.bat
pause
