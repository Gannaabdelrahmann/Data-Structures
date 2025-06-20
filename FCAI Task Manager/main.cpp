// First student: Ganna Mohamed Abdelrahman
// ID: 20236024
// Second student: Lana Mohamed Fathy
// ID: 20236074

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "BST.h"
#include "Heap.h"

using namespace std;

// Function to convert string to lowercase for case-insensitive comparison
string tolowerstring(const string& str)
{
    string lower;
    for (size_t i = 0; i < str.length(); i++)
    {
        lower += tolower(str[i]);
    }
    return lower;
}

// Case-insensitive substring check for option 7
bool containsubstring(const string& str, const string& sub)
{
    string lower = tolowerstring(str);
    string sublower = tolowerstring(sub);
    return lower.find(sublower) != string::npos;
}

// Read tasks from input file and insert into BST
void readfile(const string& fname, BST& bst)
{
    ifstream file(fname);
    if(!file.is_open())
    {
        cout << "Error: Cannot open the file " << fname << endl;
        return;
    }
    int numoftasks;
    file >> numoftasks;
    file.ignore();    // Clear new line
    for (int i = 0; i < numoftasks; i++)
    {
        string desc;
        string cat;
        int dur;
        getline(file, desc);
        file >> dur;
        file.ignore();
        getline(file, cat);
        // Trim whitespace from category
        size_t start = cat.find_first_not_of(" \t");
        size_t end = cat.find_last_not_of(" \t");
        if (start != string::npos && end != string::npos)
            cat = cat.substr(start, end - start + 1);
        else if (start == string::npos)
            cat = "";
        bst.insert(desc, cat, dur);
        cout << "Inserted: [" << desc << ", " << dur << ", " << cat << "]" << endl;
    }
    file.close();
}

int main()
{
    // Initialization
    BST bst;           // BST for active tasks
    MinHeap completedtasks;         // Min-Heap for completed tasks
    string inputfile = "tasks.txt";  // Input file name
    
    // Read tasks from tasks.txt
    cout << "Reading tasks from " << inputfile << "..." << endl;
    readfile(inputfile, bst);        // Load tasks from file into BST
    cout << "Finished reading tasks." << endl;
    
    // Program's menu options
    while(true)
    {
        cout << "\nMenu:\n1. Insert a task\n2. Display all tasks\n3. Search for a task\n4. Remove a task\n5. Display more than\n6. Display less than\n7. Mark a task as completed by task duration and description\n8. Display all completed tasks and the number of tasks completed per category\n0. Exit\n";
        cout << "Enter your choice: ";
        
        // get user input
        int option;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid option. Please try again." << endl;
            continue;
        }
        cin.ignore();     // Clears new line
        
        // Exit condition
        if(option == 0)
        {
            cout << "Exiting Task Manager. Goodbye!" << endl;
            break;
        }
        
        switch (option)
        {
            // If user chooses option 1 (Insert a new task)
            case 1:
            {
                string desc, cat;
                int dur;
                cout << "Enter task description: ";
                getline(cin, desc);
                cout << "Enter duration: ";
                if (!(cin >> dur)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid duration. Task not added." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter category: ";
                getline(cin, cat);
                // Trim whitespace from category
                size_t start = cat.find_first_not_of(" \t");
                size_t end = cat.find_last_not_of(" \t");
                if (start != string::npos && end != string::npos)
                    cat = cat.substr(start, end - start + 1);
                else if (start == string::npos)
                    cat = "";
                // Insert into BST
                bst.insert(desc, cat, dur);
                cout << "Task added successfully." << endl;
                break;
            }
            
            // If user chooses option 2 (Display all tasks (in-order traversal))
            case 2:
            {
                cout << "All tasks: " << endl;
                bst.displayAll();
                break;
            }
            
            // If user chooses option 3 (Search by exact duration)
            case 3:
            {
                int dur;
                cout << "Enter duration to search: ";
                if (!(cin >> dur)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid duration." << endl;
                    break;
                }
                cin.ignore();
                cout << "Tasks with duration " << dur << " minutes:" << endl;
                bst.search(dur);
                break;
            }
            
            // If user chooses option 4 (Remove a task)
            case 4:
            {
                int dur;
                cout << "Enter duration: ";
                if (!(cin >> dur)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid duration." << endl;
                    break;
                }
                cin.ignore();
                bst.remove(dur);
                cout << "Tasks with duration " << dur << " removed." << endl;
                break;
            }
            
            // If user chooses option 5 (Display tasks with duration larger than or equal a specified value)
            case 5:
            {
                int dur;
                cout << "Enter duration: ";
                if (!(cin >> dur)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid duration." << endl;
                    break;
                }
                cin.ignore();
                bst.displaymoreThan(dur);
                break;
            }
            
            // If user chooses option 6 (Display tasks with duration less than or equal a specified value)
            case 6:
            {
                int dur;
                cout << "Enter duration: ";
                if (!(cin >> dur)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid duration." << endl;
                    break;
                }
                cin.ignore();
                bst.displaylessThan(dur);
                break;
            }
            
            // Mark a task as completed by duration and partial description
            case 7:
            {
                int dur;
                string desc;
                cout << "Enter duration: ";
                if (!(cin >> dur)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid duration." << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter task description (partial, case-insensitive): ";
                getline(cin, desc);
                // Attempt to remove task from BST and store it
                Task* removedtask = nullptr;
                if(bst.removeTaskbydurationAndDescription(dur, desc, removedtask))
                {
                    // Insert removed task into MinHeap
                    completedtasks.insert(*removedtask);
                    cout << "Task marked as completed and moved to heap." << endl;
                    // Free memory for removed task
                    delete removedtask;
                }
                else
                {
                    cout << "Task not found." << endl;
                }
                break;
            }
            
            // Display all completed tasks and the number of tasks completed per category
            case 8:
            {
                completedtasks.display();
                break;
            }     
            
            // Default case to handle invalid input
            default:
            {
                cout << "Invalid option. Please try again." << endl;
            }
        }
    }   

    return 0;
}