#include "./customer.hpp"
#include <stdexcept>

float Customer::getArrivalTime() {
    return arrivalTime;
}

void Customer::setArrivalTime(float time) {
    this->arrivalTime = time;
}

float Customer::getStartOfServiceTime() {
    return startOfServiceTime;
}

void Customer::setStartOfServiceTime(float time) {
    this->startOfServiceTime = time;
}

float Customer::getDepartureTime() {
    return departureTime;
}

void Customer::setDepartureTime(float time) {
    this->departureTime = time;
}

int Customer::getEventStatus() {
    return eventStatus;
}

void Customer::setEventStatus(int status) {
    this->eventStatus = status;
}

Customer* Customer::getNext() {
    return next;
}

void Customer::setNext(Customer* cust) {
    this->next = cust;
}

float Customer::getEventTime() {
    switch(eventStatus) {
        case ARRIVAL:
            return arrivalTime;
        case DEPARTURE:
            return departureTime;
        case NULL_STATUS:
        default:
            throw std::runtime_error("Invalid Event Flag");
    }
}

Customer::Customer() {
    setArrivalTime(-1);
    setStartOfServiceTime(-1);
    setDepartureTime(-1);
    setEventStatus(NULL_STATUS);
    setNext(nullptr);
}
