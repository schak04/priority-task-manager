#!/bin/bash

set -e  # Stop the script if any command fails

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Normalize paths based on script location
ROOT_DIR="$SCRIPT_DIR/.."
SRC_DIR="$ROOT_DIR/src"
LIB_DIR="$ROOT_DIR/lib"
BUILD_DIR="$ROOT_DIR/build"
BIN_DIR="$ROOT_DIR/bin"

# Ensure build and bin directories exist
mkdir -p "$BUILD_DIR" "$BIN_DIR"

echo "Compiling SQLite source..."
gcc -c "$LIB_DIR/sqlite3.c" -o "$BUILD_DIR/sqlite3.o"

echo "Compiling C++ source..."
g++ -c "$SRC_DIR/task_manager.cpp" -o "$BUILD_DIR/task_manager.o"

echo "Linking to create executable..."
g++ "$BUILD_DIR/task_manager.o" "$BUILD_DIR/sqlite3.o" -o "$BIN_DIR/task_manager" -static

echo
echo "Build complete. Run with: $BIN_DIR/task_manager"