#include "linked-list.hpp"

// Default Constructor
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

// Destructor to free all nodes
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->getNext();
        delete current;
        current = next;
    }
}

// Push a new node with paired userID and password data to the back of the list
void LinkedList::push_back(pair<string, string> data) {
    Node* newNode = new Node(data);

    if (empty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
}

// Check if the list is empty
bool LinkedList::empty() {
    return head == nullptr;
}