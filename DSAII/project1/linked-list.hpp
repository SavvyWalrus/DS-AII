#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "node.hpp"
using namespace std;

// Basic singly linked list class
class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void push_back(pair<string, string> data); // Add a node to the end
        bool empty(); // Check if the list is empty
        Node* getHead() {return head;}
    private:
        Node* head; // Points to the first node in the list
        Node* tail; // Points to the last node in the list
};

#endif
