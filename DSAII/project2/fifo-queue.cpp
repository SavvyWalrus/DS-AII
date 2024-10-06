#include "./fifo-queue.hpp"

FIFOQueue::FIFOQueue() {
    this->front = nullptr;
    this->back = nullptr;
    size = 0;
}

FIFOQueue::~FIFOQueue() {
    while(front != nullptr) {
        Customer* temp = front;
        front = front->getNext();
        delete temp;
    }
}

Customer* FIFOQueue::getFront() {
    return front;
}

void FIFOQueue::setFront(Customer* cust) {
    this->front = cust;
}

Customer* FIFOQueue::getBack() {
    return back;
}

void FIFOQueue::setBack(Customer* cust) {
    this->back = cust;
}

int FIFOQueue::getSize() {
    return size;
}

void FIFOQueue::setSize(int size) {
    this->size = size;
}

Customer* FIFOQueue::dequeue() {
    if (size == 0) return nullptr;

    Customer* temp = front;

    front = front->getNext();
    if (front == nullptr) back = nullptr;

    --size;
    return temp;
}

void FIFOQueue::enqueue(Customer* cust) {
    if (front == nullptr && back == nullptr) {
        front = cust;
        back = cust;
    } else {
        back->setNext(cust);
        back = cust;
    }

    ++size;
}
