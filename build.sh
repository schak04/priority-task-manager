#!/bin/bash

echo "Compiling SQLite source..."
gcc -c sqlite3.c -o sqlite3.o

echo "Compiling C++ source..."
g++ -c task_manager.cpp -o task_manager.o

echo "Linking both to create executable..."
g++ task_manager.o sqlite3.o -o task_manager -static

echo
echo "Build complete. Run it with: ./task_manager"