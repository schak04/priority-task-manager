#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class Task {
    public:
    int priority;
    string taskName;
    string taskDesc;
    string date;
    bool completed;
};

// Comparator for Task to make a min-heap (lower value = higher priority)
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
        priority_queue<Task, vector<Task>, CompareTask> temp = tasks; // temp priority queue
        
        while (!temp.empty()) {
            tasksVec.push_back(temp.top());
            temp.pop();
        }
    }

    // function to update a task
    void updateTask() {
        showAllTasks(); // for user to choose which one to update

        makeTasksVec(); // to be able to access and update by index

        cout << "Which task do you want to update? (Enter task no.): "; int tn; cin >> tn;
        cout << "Alright. Updating Task " << tn << "...\n";

        cout << "Enter a new name for the task \"" << tasksVec[tn].taskName << "\": ";
        string newName; getline(cin, newName);
        tasksVec[tn].taskName = newName;
        
        cout << "Enter a new description for the task \"" << tasksVec[tn].taskName << "\": ";
        string newDesc; getline(cin, newDesc);
        tasksVec[tn].taskDesc = newDesc;
        
        cout << "Enter a new due date for the task \"" << tasksVec[tn].taskName << "\": ";
        string newDate; getline(cin, newDate);
        tasksVec[tn].date = newDate;

        cout << "Enter a new priority for the task \"" << tasksVec[tn].taskName << "\": ";
        int newPriority; cin >> newPriority;
        tasksVec[tn].priority = newPriority;
    }

    // function to mark a task as completed
    void markAsCompleted() {
        showAllTasks(); // for user to choose which one to mark as 'completed'

        makeTasksVec(); // to access by index and set the completed flag to 'true'

        cout << "Which task would you like to mark as completed? (Enter task no.): "; int tn; cin>>tn;
        tasksVec[tn].completed = true;
        cout << "Selected task marked as completed.";
    }
    
    // function to remove a task
    void removeTask() {
        showAllTasks(); // for user to choose which one to remove
        
        makeTasksVec(); // to access by index and remove
        
        cout << "Which task would you like to remove? (Enter task no.): "; int tn; cin>>tn;
        // deletion yet to be implemented
    }

    // function to remove or clear all the tasks
    void clearAllTasks() {};
};

void printWelcomePage() {
    cout << "=================================================================\n";
    cout << "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Priority Task Manager ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n";
    cout << "=================================================================\n";
    cout << "| ~ ~ ~ ~ ~ ~ ~ ~ Manage your tasks efficiently ~ ~ ~ ~ ~ ~ ~ ~ |\n";
    cout << "=================================================================\n";
    cout << "What's your first name? "; string fname; cin>>fname;
    cout << "\nWhat would you like to do, " << fname << "?\n";
    cout << "1. Add Task\n";
    cout << "2. Update Task\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Show All Tasks\n";
    cout << "5. Remove Task\n";
    cout << "6. Clear All Tasks\n";
    cout << "0. Exit\n";
    cout << "=================================================================\n";
}

int main() {
    printWelcomePage();
    TaskManager tm;
    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            Task t;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, t.taskName);
            cout << "Enter task description: ";
            getline(cin, t.taskDesc);
            cout << "Enter due date (DD-MM-YYYY): ";
            getline(cin, t.date);
            cout << "Enter priority (1 = highest priority): ";
            while (true) {
                cin >> t.priority;
                if (t.priority >= 1) break;
                cout << "Invalid input. Please enter a positive integer (1 = highest priority): ";
            }
            t.completed = false;
            tm.addTask(t);
            cout << "Task added successfully!\n";
            break;
        }
        case 2: {
            tm.updateTask();
            break;
        }
        case 4: {
            tm.showAllTasks();
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

    return 0;
}