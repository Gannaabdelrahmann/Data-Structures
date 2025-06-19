#include <iostream>

using namespace std;

// Node class representing a character in the double linked list 
class node {
public:
    char info;         // Character data stored in the node
    node* next;        // Pointer to the node
    node* previous;    // Pointer to the node
// Default constructor
    node() {
        info = 0;
        next = previous = nullptr;
    }
// Parameterized constructor
    node(char n, node* nex, node* p) {
        info = n;
        next = nex;
        previous = p;
    }
};

// Double linked list class for storing and manipulating a string
class charDLL {
private:
    node* head;
    node* tail;

public:
// Default constructor initializing an empty list
    charDLL() {
        head = tail = nullptr;
    }
// Constructor to initialize the list with a given string
    charDLL(string word) {
        head = tail = nullptr;
        for (char c : word) {
            addtotail(c);
        }
    }
// Destructor to free allocated memory
    ~charDLL() {
        node* curr = head;
        while (curr) {
            node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
// Adds a character to the end of the list
    void addtotail(char elem) {
        node* newnode = new node(elem, nullptr, tail);
        if (!tail) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
    }
// Removes the first character from the list
    void removefromhead() {
        if (!head) {
            cout << "The list is empty." << endl;
            return;
        }
        node* temp = head;
        head = head->next;
        if (head) head->previous = nullptr;
        else tail = nullptr;
        delete temp;
    }
// Removes the last character from the list
    void removefromtail() {
        if (!head) {
            cout << "The list is empty." << endl;
            return;
        }
        node* temp = tail;
        tail = tail->previous;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

// Removes a character at a specific index
void removalbyind(int ind)
{
    if (head == nullptr)
    {
        cout << "The list is empty, there's nothing to remove";
    }
    node * curr = head;
    int c = 0;
    while (curr != nullptr && c <ind)
    {
        curr = curr -> next;
        c++;
    }
    if (curr == nullptr)
    {
        cout << "The given index is out of the lists's bounds.";
    }
    if(curr == head)
    {
        removefromhead();
    }
    else if(curr == tail)
    {
        removefromtail();
    }
    else 
    {
        curr -> previous -> next = curr -> next;
        curr -> next -> previous = curr -> previous;
    }
    delete curr;
}
// Counts and displays the length of the list
    void getlength() {
        int count = 0;
        node* curr = head;
        while (curr) {
            count++;
            curr = curr->next;
        }
        cout << "The string's length is: " << count << endl;
    }
// Searches for a substring in the list
    int searchthelist(const string& sub) {
        node* curr = head;
        int ind = 0;
        while (curr) {
            node* temp = curr;
            int i = 0;
            while (temp && i < sub.size() && temp->info == sub[i]) {
                temp = temp->next;
                i++;
            }
            if (i == sub.size()) return ind;
            curr = curr->next;
            ind++;
        }
        return -1;
    }
// Extracts a substring from the list starting at "si" with length "sublength"
    string subextract(int si, int sublength) {
        string wantedsub = "";
        node* curr = head;
        for (int i = 0; i < si && curr; i++) curr = curr->next;
        while (curr && sublength > 0) {
            wantedsub += curr->info;
            curr = curr->next;
            sublength--;
        }
        return wantedsub;
    }
// Replaces occurrences of "oldsubstr" with "newsubstr" in the list
    void replacestring(const string& newsubstr, const string& oldsubstr) {
        if (!head || oldsubstr.empty()) {
            cout << "The list is empty." << endl;
            return;
        }
        int ind = searchthelist(oldsubstr);
        while (ind != -1) {
            node* begin = head;
            for (int i = 0; i < ind; i++) begin = begin->next;
            node* end = begin;
            for (int i = 0; i < oldsubstr.length(); i++) end = end->next;

            if (begin->previous) begin->previous->next = end;
            if (end) end->previous = begin->previous;
            if (begin == head) head = end;
            if (!end) tail = begin->previous;

            while (begin != end) {
                node* temp = begin;
                begin = begin->next;
                delete temp;
            }

            node* old = (end) ? end->previous : tail;
            for (char g : newsubstr) {
                node* newnode = new node(g, nullptr, old);
                if (old) old->next = newnode;
                old = newnode;
                if (!head) head = newnode;
            }
            if (end) old->next = end;
            else tail = old;

            ind = searchthelist(oldsubstr);
        }
    }
// Concates another double linked list to the current list
    void concatstrings(const charDLL& L2) {
        if (L2.head == nullptr) {
            cout << "The given string is empty, there's nothing to concatenate." << endl;
            return;
        }
        if (head == nullptr)
        {
            head = L2.head;
            tail = L2.tail;
        }
        else
        {
            tail -> next = L2.head;
            L2.head -> previous = tail;
            tail = L2.tail;
        }
    }
// Displays the list contents
    void display() {
        node* curr = head;
        cout << "The double linked list: ";
        while (curr) {
            cout << curr->info;
            curr = curr->next;
            cout << " ";
        }
        cout <<endl;
        cout << "End of DLL." << endl;
    }

    friend ostream& operator<<(ostream& out, const charDLL& list) {
        node* curr = list.head;
        while (curr) {
            out << curr->info;
            curr = curr->next;
        }
        return out;
    }
};
// Main function
int main()
{
    string s1, s2;
    cout << "Enter string to add to list 1: ";
    cin >> s1;
    charDLL l1(s1);

    cout << "Enter string to add to list 2: ";
    cin >> s2;
    charDLL l2(s2);

    // Concatenation
    l1.concatstrings(l2);
    cout << "Concatenated Lists: " << l1 << endl;

    // Remove character by index
    int index;
    cout << "Choose a character by index to remove: ";
    cin >> index;
    // Implement function to remove character by index in your class
    l1.removalbyind(index);
    cout << "List after removal: " << l1 << endl;

    // Substring Extraction
    int start, len;
    cout << "Enter index and length to get substring: ";
    cin >> start >> len;
    cout << "Substring: " << l1.subextract(start, len) << endl;

    // Search
    string searchStr;
    cout << "Search for a string in the list: ";
    cin >> searchStr;
    int foundIndex = l1.searchthelist(searchStr);
    if (foundIndex != -1)
        cout << "Found at index " << foundIndex << endl;
    else
        cout << "Not found!" << endl;

    // Replacement
    string oldSub, newSub;
    cout << "Enter 2 substrings to replace one with another: ";
    cin >> oldSub >> newSub;
    l1.replacestring(newSub, oldSub);
    cout << "List after replacement: " << l1 << endl;

    return 0;
}

