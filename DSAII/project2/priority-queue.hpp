#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "./customer.hpp"
#define MAX_P_QUEUE_SIZE 200

class PriorityQueue {
    private:
        Customer* customerEvents[MAX_P_QUEUE_SIZE];
        int size;
    public:
        PriorityQueue();
        int getSize();
        void setSize(int size);
        void enqueue(Customer* cust);
        Customer* dequeue();
        Customer* peek();
};

#endif