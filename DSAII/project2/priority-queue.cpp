#include "./priority-queue.hpp"
#include "customer.hpp"
#include <stdexcept>

PriorityQueue::PriorityQueue() {
    size = 0;
}

int PriorityQueue::getSize() {
    return size;
}

// void PriorityQueue::setSize(int size) {
//     if (size <= MAX_P_QUEUE_SIZE) this->size = size;
// }

void PriorityQueue::enqueue(Customer* cust) {
    if (size >= MAX_P_QUEUE_SIZE) {
        throw std::overflow_error("Heap is full");
    }

    // Inserts a customer to the end of the array
    customerEvents[size] = cust;
    int currIndex = size;
    ++size;

    // Heapify up
    while (currIndex > 0) {
        int parentIndex = (currIndex - 1) / 2;

        // Checks for higher priority
        if (customerEvents[currIndex]->getEventTime() < customerEvents[parentIndex]->getEventTime()) {
            // Swaps current customer and parent
            Customer* temp = customerEvents[currIndex];
            customerEvents[currIndex] = customerEvents[parentIndex];
            customerEvents[parentIndex] = temp;

            // Assigns currIndex to the new position
            currIndex = parentIndex;
        } else {
            break;
        }
    }
}

Customer* PriorityQueue::dequeue() {
    Customer* cust = peek();
    customerEvents[0] = customerEvents[size - 1];
    --size;

    int currIndex = 0;

    // Heapify down
    while (currIndex < size / 2) {
        int leftChildIndex = currIndex * 2 + 1;
        int rightChildIndex = leftChildIndex + 1;
        int smallestIndex = currIndex;

        // Checks for higher priority and assigns result's index to smallestIndex
        if (customerEvents[leftChildIndex]->getEventTime() < customerEvents[smallestIndex]->getEventTime()) {
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < size && customerEvents[rightChildIndex]->getEventTime() < customerEvents[smallestIndex]->getEventTime()) {
            smallestIndex = rightChildIndex;
        }

        // Swaps with child if child is higher priority, breaks if current customer has highest priority
        if (smallestIndex != currIndex) {
            Customer* temp = customerEvents[currIndex];
            customerEvents[currIndex] = customerEvents[smallestIndex];
            customerEvents[smallestIndex] = temp;

            currIndex = smallestIndex;
        } else {
            break;
        }
    }

    return cust;
}

Customer* PriorityQueue::peek() {
    if (size <= 0) return nullptr;

    return customerEvents[0];
}
