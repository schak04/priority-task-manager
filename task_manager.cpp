#include <iostream>
#include <string>
#include <queue>
#include <vector>
extern "C" {
    #include "sqlite3.h"
}
sqlite3* db;
using namespace std;

class Task {
    public:
    int priority;
    string taskName;
    string taskDesc;
    string date;
    bool completed;
};

// comparator for Task to make a min-heap (lower value = higher priority)
struct CompareTask {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority > b.priority;
    }
};

class TaskManager {
    public:
    priority_queue<Task, vector<Task>, CompareTask> tasks; // priority queue 'tasks'
    
    vector<Task> tasksVec; // vector to store tasks from the priority queue when accessing by index would be needed

    // function to add a task
    void addTask(Task task) {
        tasks.push(task);
        cout << "Task added successfully.\n";
    }

    // function to display all the tasks
    void showAllTasks() {
        if (tasks.empty()) {
            cout << "No tasks to show.\n"; return;
        }
        // copy 'tasks' to 'temp' to display all the tasks without removing them from 'tasks'
        priority_queue<Task, vector<Task>, CompareTask> temp = tasks;
        int idx = 1;
        while (!temp.empty()) {
            Task task = temp.top();
            cout << "--------------------------\n";
            cout << "Task " << idx++ << "\n";
            cout << "Priority: " << task.priority << "\n";
            cout << "Task Name: " << task.taskName << "\n";
            cout << "Description: " << task.taskDesc << "\n";
            cout << "Due date: " << task.date << "\n";
            cout << "Completed: " << (task.completed ? "Yes" : "No") << "\n";
            temp.pop();
        }
        cout << "--------------------------\n";
    }

    // helper function to extract all the tasks from the priority queue into a vector
    void makeTasksVec() {
        tasksVec.clear(); // clear old data
        priority_queue<Task, vector<Task>, CompareTask> temp = tasks; // temp priority queue
        
        while (!temp.empty()) {
            tasksVec.push_back(temp.top());
            temp.pop();
        }
    }

    // helper function to rebuild the priority queue
    void rebuildPriorityQueue() {
        tasks = priority_queue<Task, vector<Task>, CompareTask>();
        for (Task& t : tasksVec) tasks.push(t);
    }

    // function to update a task
    void updateTask() {
        showAllTasks();
        makeTasksVec();

        cout << "Which task do you want to update? (Enter task no.): "; int tn; cin >> tn;
        cin.ignore(); // flush newline
        tn--; // convert to 0-indexed

        if (tn < 0 || tn >= tasksVec.size()) {
            cout << "Invalid task number.\n";
            return;
        }
        
        cout << "Alright. Updating Task " << tn+1 << "...\n";

        cout << "Enter a new name for the task \"" << tasksVec[tn].taskName << "\": ";
        getline(cin, tasksVec[tn].taskName);
                
        cout << "Enter a new description for the task \"" << tasksVec[tn].taskName << "\": ";
        getline(cin, tasksVec[tn].taskDesc);
        
        cout << "Enter a new due date for the task \"" << tasksVec[tn].taskName << "\": ";
        getline(cin, tasksVec[tn].date);

        cout << "Enter a new priority for the task \"" << tasksVec[tn].taskName << "\": ";
        cin >> tasksVec[tn].priority;
        
        rebuildPriorityQueue();

        cout << "Task updated successfully.\n";
    }

    // function to mark a task as completed
    void markAsCompleted() {
        showAllTasks();
        makeTasksVec();

        cout << "Which task would you like to mark as completed? (Enter task no.): "; int tn; cin>>tn; tn--;
        tasksVec[tn].completed = true;

        rebuildPriorityQueue();

        cout << "Selected task marked as completed.\n";
    }
    
    // function to remove a task
    void removeTask() {
        showAllTasks();
        makeTasksVec();
        
        cout << "Which task would you like to remove? (Enter task no.): "; int tn; cin>>tn; tn--;

        if (tn < 0 || tn >= tasksVec.size()) {
            cout << "Invalid task number.\n";
            return;
        }

        tasksVec.erase(tasksVec.begin()+tn);

        rebuildPriorityQueue();
        
        cout << "Task removed successfully.\n";
    }

    // function to clear all the tasks
    void clearAllTasks() {
        while (!tasks.empty()) tasks.pop();
        tasksVec.clear();
        cout << "Clearing all the tasks...\nAll tasks cleared.\n";
    }

    // function to add tasks to database
    bool addTaskToDB(const Task& t) {
        const char* sql = "INSERT INTO tasks (name, description, due_date, priority, completed) VALUES (?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
            return false;
        }

        // bind values
        sqlite3_bind_text(stmt, 1, t.taskName.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, t.taskDesc.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, t.date.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, t.priority);
        sqlite3_bind_int(stmt, 5, t.completed ? 1 : 0);

        // execute
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Failed to insert task: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
        return true;
    }

};

string fname;

void printWelcomePage() {
    cout << "=================================================================\n";
    cout << "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Priority Task Manager ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n";
    cout << "=================================================================\n";
    cout << "| ~ ~ ~ ~ ~ ~ ~ ~ Manage your tasks efficiently ~ ~ ~ ~ ~ ~ ~ ~ |\n";
    cout << "=================================================================\n";
    cout << "What's your first name? "; cin>>fname; cout<<"\n";
}

void printMenu() {
    cout << "=================================================================\n";
    cout << "What would you like to do, " << fname << "?\n";
    cout << "1. Add Task\n";
    cout << "2. Update Task\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Show All Tasks\n";
    cout << "5. Remove Task\n";
    cout << "6. Clear All Tasks\n";
    cout << "0. Exit\n";
    cout << "=================================================================\n";
}

bool initDB() {
    int rc = sqlite3_open("tasks.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            due_date TEXT,
            priority INTEGER,
            completed INTEGER
        );
    )";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

int main() {
    if (!initDB()) {
        cerr << "Database initialization failed. Exiting...\n";
        return 1;
    }

    printWelcomePage();
    TaskManager tm;
    int choice;
    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            Task t;
            cout << "Enter task name: "; cin.ignore(); getline(cin, t.taskName);
            cout << "Enter task description: "; getline(cin, t.taskDesc);
            cout << "Enter due date (DD-MM-YYYY): "; getline(cin, t.date);
            cout << "Enter priority (1 = highest priority): ";
            while (true) {
                cin >> t.priority;
                if (t.priority >= 1) break;
                cout << "Invalid input. Please enter a positive integer (1 = highest priority): ";
            }
            t.completed = false;
            if (tm.addTaskToDB(t)) {
                tm.addTask(t);
                cout << "Task added to database successfully.\n";
            } else {
                cout << "Failed to add task to database.\n";
            }
            break;
        }
        case 2: {
            tm.updateTask();
            break;
        }
        case 3: {
            tm.markAsCompleted();
            break;
        }
        case 4: {
            tm.showAllTasks();
            break;
        }
        case 5: {
            tm.removeTask();
            break;
        }
        case 6: {
            tm.clearAllTasks();
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid input. Please enter a valid option.\n";
            break;
        }
    } while (choice != 0);

    sqlite3_close(db);
    return 0;
}