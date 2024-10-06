#ifndef FIFO_QUEUE
#define FIFO_QUEUE
#include "./customer.hpp"

class FIFOQueue {
    private:
        // Pointers for front and end of queue
        Customer* front;
        Customer* back;

        // Current size
        int size = 0;
    public:
        // Default constructor
        FIFOQueue();

        // Destructor
        ~FIFOQueue();

        // Getters and Setters
        Customer* getFront();
        void setFront(Customer* cust);
        Customer* getBack();
        void setBack(Customer* cust);
        int getSize();
        void setSize(int size);

        // Queue functions
        Customer* dequeue();
        void enqueue(Customer* cust);
};

#endif