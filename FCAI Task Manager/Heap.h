// First student: Ganna Mohamed Abdelrahman
// ID: 20236024
// Second student: Lana Mohamed Fathy
// ID: 20236074

#include <iostream>
#include <string>
#include <cctype>
#include "BST.h" // Include BST.h to use the same Task class
#ifndef HEAP_H
#define HEAP_H

using namespace std;

// MinHeap class
class MinHeap
{
private:
    Task* heap;   // dynamic array to store the completed tasks
    int size;
    int capacity;

    // Function to convert string to lowercase and trim whitespace
    string normalizeCategory(const string& cat) {
        string result = cat;
        // Trim leading and trailing whitespace
        size_t start = result.find_first_not_of(" \t");
        size_t end = result.find_last_not_of(" \t");
        if (start != string::npos && end != string::npos)
            result = result.substr(start, end - start + 1);
        else if (start == string::npos)
            result = "";
        // Convert to lowercase
        for (char &c : result) c = tolower(c);
        return result;
    }

    // Function to get the position of the parent
    int parent(int index)
    {
        return (index-1)/2;
    }
    // Function to get the position of the right child
    int rightchild(int index)
    {
        return 2*index + 2;
    }
    // Function to get the position of the left child
    int leftchild(int index)
    {
        return 2*index + 1;
    }
    // Swap function
    void swap(Task& a, Task& b)
    {
        Task temp = a;
        a = b;
        b = temp;
    }
    // MinHeapify to maintain the heap property
    void MinHeapify(int index)
    {
        int smallest = index;
        int left = leftchild(index);
        int right = rightchild(index);
        if (left < size && heap[left].duration < heap[smallest].duration)
        {
            smallest = left;
        }
        if (right < size && heap[right].duration < heap[smallest].duration)
        {
            smallest = right;
        }
        if (smallest != index)
        {
            swap(heap[index], heap[smallest]);
            MinHeapify(smallest);    // Recursively heapify the affected subtree
        }
    }
    // siftup to move a node up during insertion
    void siftup(int index)
    {
        while (index > 0 && heap[parent(index)].duration > heap[index].duration)
        {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    // resize function to resize the dynamic array when it is full
    void resize()
    {
        int newcapacity = capacity * 2;
        Task* newheap = new Task[newcapacity];
        // Loop to copy the existing elements 
        for (int i = 0; i < size; i++)
        {
            newheap[i] = heap[i];
        }
        // Frees the old array and updates the heap
        delete[] heap;
        heap = newheap;
        capacity = newcapacity;
    }

public:
    // Default constructor
    MinHeap()
    {
        size = 0;
        int initialcap = 10;
        capacity = initialcap;
        heap = new Task[capacity];
    }
    // Destructor to free the dynamic array
    ~MinHeap()
    {
        delete[] heap;
    }
    // Insert a task into the heap
    void insert(Task task)
    {
        if (size >= capacity)
        {
            resize();   // Doubles the capacity
        }
        heap[size] = task;
        siftup(size);    // To maintain the heap property
        size++;
    }
    // Display all tasks and category counts
    void display()
    {
        if (size == 0)
        {
            cout << "No completed tasks." << endl;
        }
        else {
            // Copy heap to a temporary dynamic array and sort by duration
            Task* temp = new Task[size];
            int tempsize = size;
            for(int i = 0; i < size; i++)
            {
                temp[i] = heap[i];
            }
            // Bubble sort to display in ascending order 
            // Note: Could optimize by using heap properties directly
            for (int i = 0; i < tempsize-1; i++)
            {
                for (int j = 0; j < tempsize-i-1; j++)
                {
                    if (temp[j].duration > temp[j+1].duration)
                    {
                        swap(temp[j], temp[j+1]);
                    }
                }
            }
            // Display completed tasks
            cout << "Completed tasks: " << endl;
            for (int i = 0; i < tempsize; i++)
            {
                cout << "Task #" << i+1 << ": "; 
                temp[i].print();
                cout << endl;
            }
            // Free temporary array
            delete[] temp;
        }
        // Count categories manually
        int educational = 0, health = 0, selfdevelop = 0, food = 0, other = 0;
        for(int i = 0; i < size; i++)
        {
            string normCat = normalizeCategory(heap[i].category);
            if (normCat == "educational")
                educational++;
            else if (normCat == "health")
                health++;
            else if (normCat == "self development")
                selfdevelop++;
            else if (normCat == "food")
                food++;
            else if (normCat == "other")
                other++;
        }
        // Display category counts, including zeros
        cout << "\nNumber of completed tasks per category: " << endl;
        cout << "Educational: " << educational << endl;
        cout << "Health: " << health << endl;
        cout << "Self development: " << selfdevelop << endl;
        cout << "Food: " << food << endl;
        cout << "Other: " << other << endl;
    }
};

#endif