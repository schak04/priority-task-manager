# Priority-Based Task Manager

![C++](https://img.shields.io/badge/C++-blue?style=flat-square&logo=c%2B%2B&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-07405E?style=flat-square&logo=sqlite&logoColor=white)

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

## Run on Windows (Prebuilt App Bundle; No Cloning and Building Required to Run)

If you're a regular user and just want to **run the app on Windows**, follow these steps:

**Either: Download the installer `prioritytaskmanager_setup.exe` and install the app bundle using it.**

**Or:**

1. **Go to the [Releases](https://github.com/schak04/priority-task-manager/releases) section of this repo.**
2. **Download the `.zip` bundle** attached to the latest release.
3. **Extract** the zip file.
4. Open the extracted folder and go to the `bin/` directory.
5. **Double-click `task_manager.exe`** to run the app.

> **Do not move the EXE out of the `bin/` folder.**

---

## How to Build and Run

### Clone the Repository

```bash
git clone https://github.com/schak04/priority-task-manager.git
cd priority-task-manager
```

### On Windows

**Build:**

Go to `scripts` -> Double-click `build.bat`.

Or run the script via terminal:

```cmd
scripts\build.bat
```

**Run:**

Go to `scripts` -> Double-click `run.bat`.

Or run the script via terminal:

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

## Project Structure

```bash
priority-task-manager/
│
├── bin/         <- Final executable goes here
├── build/       <- Object files go here
├── data/        <- SQLite database file
├── lib/         <- sqlite3.c and sqlite3.h
├── scripts/     <- Build and run scripts
├── src/         <- Main C++ source code
├── .gitattributes
├── .gitignore
├── README.md
```

> All directories (like bin/, build/, data/) are auto-created during build. No need to create them manually.

---

## Current Status

- Core features implemented
- Fully functional CLI app
- GUI integration in progress

---

## Author

Copyright (c) 2025 [Saptaparno Chakraborty](https://github.com/schak04).  
All rights reserved.

---
