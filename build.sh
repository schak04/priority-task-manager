#!/bin/bash

# Build sqlite3.c with C compiler
gcc -c sqlite3.c -o sqlite3.o

# Build your C++ file
g++ -c task_manager.cpp -o task_manager.o

# Link them together
g++ task_manager.o sqlite3.o -o task_manager -static

echo
echo "Build complete. Run it with: ./task_manager"