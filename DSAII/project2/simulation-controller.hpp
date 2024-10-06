#ifndef SIMULATION_CONTROLLER_HPP
#define SIMULATION_CONTROLLER_HPP

#include "./math-model.hpp"
#include "./fifo-queue.hpp"
#include "./priority-queue.hpp"
#include "customer.hpp"
#include <string>

class SimulationController {
    private:
        MathModel model;
        FIFOQueue fQueue;
        PriorityQueue pQueue;

        float lambda;
        float mu;
        int numServiceChannels;
        int eventsToSimulate;
        int serverAvailableCnt;
        float currTime;
        float nextArrivalTime;

        int customerWaitedCnt;
        float totalWaitTime;
        float totalServiceTime;
        float idleTime;
        int customersProcessed;
        float lastDepartureTime;
        float totalCustomerTimeInSystem;
        float totalCustomerTimeInQueue;

        void clearVariables();
        void loadModel(std::string filename);
        void processStatistics(Customer* cust);
        void printStatistics();
        float generateNextRandomInterval();
        void addArrivals();
        void processNextEvent();
    public:
        SimulationController();
        void runSimulation(std::string filename);
};

#endif