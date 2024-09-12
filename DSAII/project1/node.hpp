#ifndef NODE_HPP
#define NODE_HPP

#include <string>
using namespace std;

// Node class for linked list
class Node {
    public:
        Node(pair<string, string> data) {
            this->data = data;
            next = nullptr;
        }
        void setNext(Node* next) {this->next = next;} // Sets a pointer to the next node
        Node* getNext() {return next;} // Returns a pointer to the next node
        pair<string, string> getData() {return data;} // Returns the paired userID and password
    private:
        pair<string, string> data; // Holds the userID and password pair
        Node* next; // Pointer to the next node
};

#endif