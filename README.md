# Priority-Based Task Manager

This is a console-based task manager app that helps you stay productive by prioritizing your tasks.

---

## Features

- Console interface with welcome screen
- Add, update, complete, and remove tasks
- Display all tasks (ordered by priority)
- Clear all tasks
- In-memory storage using priority queue and vector
- Persistent storage with SQLite
- Cross-platform build scripts (Windows `.bat` and Linux/macOS `.sh`)
- GUI coming soon

---

## Technologies Used

- Language: **C++**
- C++ **Standard Template Library (STL)**
- Database: **SQLite**
- Build Tools:
  - `g++` (C++)
  - `gcc` (C)
  - `.bat` and `.sh` scripts for building and running

---

## Installation

### Clone the Repository

```bash
git clone https://github.com/schak04/priority-task-manager.git
cd priority-task-manager
```

---

## Project Structure

```bash
priority-task-manager/
│
├── bin/             <- Final EXE goes here
├── build/           <- Object files (*.o) go here
├── data/            <- SQLite database file (tasks.db)
├── lib/             <- `sqlite3.c` and `sqlite3.h` (amalgamation files)
├── scripts/         <- Build and run scripts (`.bat`/`.sh`)
├── src/             <- Main C++ source code (`task_manager.cpp`)
├── .gitignore
├── README.md
```

---

## How to Build and Run

### On Windows

**Build:**

Double-click or run the script via terminal:

```cmd
scripts\build.bat
```

**Run:**

1. Go to `scripts/run.bat`
2. Double-click `run.bat`

Or:

```cmd
scripts\run.bat
```

### On Linux/macOS

#### Make the build script executable (only once)

```bash
chmod +x scripts/build.sh
```

**Build:**

```bash
./scripts/build.sh
```

**Run:**

```bash
./bin/task_manager
```

---

## Current Status

- Core features implemented
- Functional CLI app made
- GUI integration in progress

---

## Author

Copyright (c) 2025 [Saptaparno Chakraborty](https://github.com/schak04).  
All rights reserved.

---
