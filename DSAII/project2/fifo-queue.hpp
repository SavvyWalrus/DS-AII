#ifndef FIFO_QUEUE
#define FIFO_QUEUE
#include "./customer.hpp"

class FIFOQueue {
    private:
        Customer* front;
        Customer* back;
        int size = 0;
    public:
        FIFOQueue();
        ~FIFOQueue();
        Customer* getFront();
        void setFront(Customer* cust);
        Customer* getBack();
        void setBack(Customer* cust);
        int getSize();
        void setSize(int size);
        Customer* dequeue();
        void enqueue(Customer* cust);
};

#endif