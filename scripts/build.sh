#!/bin/bash

set -e  # stop the script if any command fails

echo "Compiling SQLite source..."
gcc -c ../lib/sqlite3.c -o ../build/sqlite3.o

echo "Compiling C++ source..."
g++ -c ../src/task_manager.cpp -o ../build/task_manager.o

echo "Linking to create executable..."
g++ ../build/task_manager.o ../build/sqlite3.o -o ../bin/task_manager -static

echo
echo "Build complete. Run with: ../bin/task_manager"