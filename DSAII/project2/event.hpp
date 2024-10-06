#ifndef EVENT_HPP
#define EVENT_HPP
#include "./customer.hpp"

class Event {
    private:
        float startTime;
        float completionTime;
        Customer* cust;
        float computeCompletionTime();
    public:
        Event(float startTime, float completionTime, Customer* cust);
        void setStartTime(float time);
        float getStartTime();
        void setCompletionTime(float time);
        float getCompletionTime();
        void setCustomer(Customer* cust);
        Customer* getCustomer();
};

#endif