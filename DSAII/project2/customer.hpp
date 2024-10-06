#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#define NULL_STATUS -1
#define ARRIVAL 0
#define DEPARTURE 1

class Customer {
    private:
        // Time arrived
        float arrivalTime;

        // Time when service starts
        float startOfServiceTime;

        // Time when service ends
        float departureTime;

        // Flag for scheduled arrival or departure event
        int eventStatus;

        // FIFO Queue pointer
        Customer* next;
    public:
        // Default constructor
        Customer();

        // Returns the proper time for priority sorting
        float getEventTime();

        // Getters and Setters
        float getArrivalTime();
        void setArrivalTime(float time);
        float getStartOfServiceTime();
        void setStartOfServiceTime(float time);
        float getDepartureTime();
        void setDepartureTime(float time);
        int getEventStatus();
        void setEventStatus(int status);
        Customer* getNext();
        void setNext(Customer* cust);
};

#endif