// First student: Ganna Mohamed Abdelrahman
// ID: 20236024
// Second student: Lana Mohamed Fathy
// ID: 20236074

#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Task class to represent a task
class Task {
public:
    string description;
    string category;
    int duration;
    Task *left;    // Pointer for the left child (used in BST, nullptr in MinHeap)
    Task *right;   // Pointer for the right child (used in BST, nullptr in MinHeap)

    // Default constructor to initialize with default values
    Task() {
        description = " ";
        duration = 0;
        category = " ";
        left = nullptr;
        right = nullptr;
    }

    // Parameterized constructor to initialize with provided values
    Task(string desc, string cat, int dur) {
        description = desc;
        category = cat;
        duration = dur;
        left = nullptr;
        right = nullptr;
    }

    // Prints task details in [description, duration, category] format
    void print() const {
        cout << "[" << description << ", " << duration << ", " << category << "]";
    }
};

// BST class for tasks, sorted by duration
class BST {
    Task *r;        // Root pointer of the BST

// Displays task's details in required format [description, duration, category]
    void displayTask(Task* node) {
        cout << "[" << node->description << ", " << node->duration << ", " << node->category << "]" << endl;
    }

// Recursively inserts a new task into the BST, sorted by duration
    Task* insert(Task *node, string DES, string CAT, int dur) 
    {
// If node is null, create new task
        if (!node) {
            return new Task(DES, CAT, dur);
        }
// Insert into left subtree if duration is less than or equal to current node's duration
        else if (dur <= node->duration) {
            node->left = insert(node->left, DES, CAT, dur);
        }
// Insert into right subtree if duration is greater
        else {
            node->right = insert(node->right, DES, CAT, dur);
        }
        return node;
    }

// Performs in-order traversal to display tasks (left, root, right)
    void inOrder(Task* node) {
        if (!node) {
            return;
        }
        inOrder(node->left);         // Visit left subtree
        displayTask(node);           // Display current task
        inOrder(node->right);        // Visit right subtree
    }

// Searches for tasks with a specific duration and displays them
    void search(Task* node, int dur) {
        if (!node) {
            return;
        }
        search(node->left, dur);      // Search left subtree
// Display task if duration matches
        if (node->duration == dur) {
            displayTask(node);
        }
        search(node->right, dur);     // Search right subtree
    }

// Displays tasks with duration greater than or equal to specified duration
    void displayMoreThan(Task* node, int dur) {
        if (!node) {
            return;
        }
        displayMoreThan(node->left, dur);       // Visit left subtree
// Displays task if duration is greater or equal to specified duration
        if (node->duration >= dur) {
            displayTask(node);
        }
        displayMoreThan(node->right, dur);      // Visit right subtree
    }

// Displays tasks with duration less than or equal to specified duration
    void displayLessThan(Task* node, int dur) {
        if (!node) {
            return;
        }
        displayLessThan(node->left, dur);       // Visit left subtree
// Displays task if duration is less than or equal to specified duration
         if (node->duration <= dur) {
            displayTask(node);
        }
        displayLessThan(node->right, dur);       // Visit right subtree
    }

// Finds the node with the minimum duration in a subtree
    Task* findmin(Task* node) {
// Traverse left until no left child exists
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

// Remove all tasks with a specified duration
    Task* remove(Task* node, int dur) {
        if (!node) {
            return nullptr;
        }
// Recursively remove from left and right subtrees
        node->left = remove(node->left, dur);
        node->right = remove(node->right, dur);

// If current node's duration matches, remove it
        if (node->duration == dur) {
// Case 1: No children
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
// Case 2: Only right child
            else if (!node->left) {
                Task* temp = node->right;
                delete node;
                return temp;
            }
// Case 3: Only left child
            else if (!node->right) {
                Task* temp = node->left;
                delete node;
                return temp;
            }
// Case 4: Two children
            else {
                Task* minnode = findmin(node->right);
                node->description = minnode->description;
                node->category = minnode->category;
                node->duration = minnode->duration;
                node->right = remove(node->right, minnode->duration);
            }
        }
        return node;
    }

// Clears all nodes in the BST (helper for destructor)
    void clear(Task* node)
    {
        if(node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

// Removes a specific task by duration and description (case-insensitive)
    Task* removeTask(Task* node, int dur, string desc, Task*& removedTask, bool& found) {
        if (!node) {
            return nullptr;
        }

        node->left = removeTask(node->left, dur, desc, removedTask, found);
        node->right = removeTask(node->right, dur, desc, removedTask, found);

        // Case-insensitive substring check
        string lowerNodeDesc = node->description;
        string lowerDesc = desc;
        for (char &c : lowerNodeDesc) c = tolower(c);
        for (char &c : lowerDesc) c = tolower(c);

        if (node->duration == dur && lowerNodeDesc.find(lowerDesc) != string::npos) {
            found = true;
            removedTask = node;
            
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Task* temp = node->right;
                node->right = nullptr;
                return temp;
            }
            else if (!node->right) {
                Task* temp = node->left;
                node->left = nullptr;
                return temp;
            }
            else {
                Task* minnode = findmin(node->right);
                node->description = minnode->description;
                node->category = minnode->category;
                node->duration = minnode->duration;
                node->right = remove(node->right, minnode->duration);
                return node;
            }
        }
        return node;
    }

public:
// Constructor initializes an empty BST
    BST() {
        r = nullptr;
    }

// Destructor frees all nodes in the BST
    ~BST() {
        clear(r);
    }

// Inserts a new task into the BST
    void insert(string DES, string CAT, int dur) {
        r = insert(r, DES, CAT, dur);
    }

// Displays all tasks in in-order traversal
    void displayAll() {
        inOrder(r);
    }

// Searches for tasks with specified duration
    void search(int dur) {
        cout << "tasks with duration " << dur << " minutes are : \n";
        search(r, dur);
    }

// Removes all tasks with specified duration
    void remove(int dur) {
        r = remove(r, dur);
        cout << "all tasks with duration " << dur << " has been removed\n";
    }

// Displays tasks with duration greater than or equal to specified duration
    void displaymoreThan(int dur) {
        cout << "tasks with duration more than or equal " << dur << ":\n";
        displayMoreThan(r, dur);
    }

// Displays tasks with duration less than or equal to specified duration
    void displaylessThan(int dur) {
        cout << "tasks with duration less than or equal " << dur << ":\n";
        displayLessThan(r, dur);
    }

// Removes a task by duration and partial description, returns true if found
    bool removeTaskbydurationAndDescription(int dur, string desc, Task*& removedtask)
    {
      bool found = false;
      r = removeTask(r, dur, desc, removedtask, found);
      return found;
    }
};

#endif