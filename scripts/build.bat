@echo off

echo Compiling SQLite source...
gcc -c ../lib/sqlite3.c -o ../build/sqlite3.o

echo Compiling C++ source...
g++ -c ../src/task_manager.cpp -o ../build/task_manager.o

echo Linking both to create executable...
g++ ../build/task_manager.o ../build/sqlite3.o -o ../bin/task_manager.exe -static

echo.
echo Build complete. Run with: scripts/run.bat
pause