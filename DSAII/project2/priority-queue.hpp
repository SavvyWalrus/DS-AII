#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "./customer.hpp"
#define MAX_P_QUEUE_SIZE 200

class PriorityQueue {
    private:
        Customer* customerEvents[MAX_P_QUEUE_SIZE]; // Array for heap based priority queue
        int size; // Current heap size
    public:
        // Default constructor
        PriorityQueue();

        // Getters and Setters
        int getSize();
        // void setSize(int size);

        // Queue functions
        void enqueue(Customer* cust);
        Customer* dequeue();
        Customer* peek();
};

#endif