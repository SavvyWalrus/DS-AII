#include "./simulation-controller.hpp"
#include "customer.hpp"
#include "priority-queue.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

void SimulationController::clearVariables() {
    currTime = 0.0;
    nextArrivalTime = 0.0;
    customerWaitedCnt = 0;
    totalWaitTime = 0.0;
    totalServiceTime = 0.0;
    idleTime = 0.0;
    customersProcessed = 0;
    lastDepartureTime = 0.0;
    totalCustomerTimeInSystem = 0.0;
    totalCustomerTimeInQueue = 0.0;
}

SimulationController::SimulationController() {
    model = MathModel();
    fQueue = FIFOQueue();
    pQueue = PriorityQueue();
    clearVariables();
}

void SimulationController::loadModel(std::string filename) {
    std::ifstream file = std::ifstream(filename);

    file >> lambda >> mu >> numServiceChannels >> eventsToSimulate;

    model.calculateNewValues(lambda, mu, numServiceChannels);
}

void SimulationController::processStatistics(Customer* cust) {
    float currWaitTime = cust->getStartOfServiceTime() - cust->getArrivalTime();

    if (currWaitTime != 0) {
        ++customerWaitedCnt;
        totalWaitTime += currWaitTime;
    }

    totalServiceTime += cust->getDepartureTime() - cust->getStartOfServiceTime();

    if (serverAvailableCnt == numServiceChannels && pQueue.getSize() > 0) {
        idleTime += pQueue.peek()->getEventTime() - cust->getDepartureTime();
    }

    ++customersProcessed;
}

void SimulationController::printStatistics() {
    // Utilization factor calculation
    float utilizationFactor = totalServiceTime / (numServiceChannels * lastDepartureTime);
    
    // Set up formatting
    int labelWidth = 58;  // Width for the statistic labels
    int valueWidth = 10;  // Width for the statistic values

    std::cout << std::left << std::setw(labelWidth - 2) << std::setfill(' ') << std::left << "\nStatistic type" << std::right << std::setw(valueWidth) << "Actual : Model prediction\n" <<
                std::setw(80) << std::setfill('-') << "" << std::endl;

    std::cout << std::setfill(' ');

    std::cout << std::left << std::setw(labelWidth - 1) << std::left << std::fixed << std::setprecision(5) << "Percentage idle time: "
                << std::right << std::setw(valueWidth) << idleTime / lastDepartureTime * 100 << "% : " << model.getIdleTime() * 100 << "%" << std::endl;
    
    std::cout << std::left << std::setw(labelWidth) << std::left << std::setprecision(6) << "Average number of customers in the system "
                << std::right << std::setw(valueWidth) << totalCustomerTimeInSystem / lastDepartureTime << " : " << model.getAvgNumPeople() << std::endl;
    
    std::cout << std::left << std::setw(labelWidth) << std::left << "Average time spent in the system by a customer "
                << std::right << std::setw(valueWidth) << totalCustomerTimeInSystem / customersProcessed << " : " << model.getAvgTotalTime() << std::endl;
    
    std::cout << std::left << std::setw(labelWidth) << std::left << "Average number of customers in the queue "
                << std::right << std::setw(valueWidth) << totalCustomerTimeInQueue / lastDepartureTime << " : " << model.getAvgQueueNum() << std::endl;
    
    std::cout << std::left << std::setw(labelWidth) << std::left << "Average time spent waiting in the queue "
                << std::right << std::setw(valueWidth) << totalWaitTime / customersProcessed << " : " << model.getAvgTimeInQueue() << std::endl;
    
    std::cout << std::left << std::setw(labelWidth) << std::left << "Utilization factor "
                << std::right << std::setw(valueWidth) << utilizationFactor << " : " << model.getUtilization() << std::endl;
    
    std::cout << std::left << std::setw(labelWidth - 1) << std::left << std::setprecision(5) << "Probability of waiting for service "
                << std::right << std::setw(valueWidth) << static_cast<float>(customerWaitedCnt) / customersProcessed * 100 << "% : N/A" << std::endl;
}

void SimulationController::addArrivals() {
    for (int i = pQueue.getSize(); i < MAX_P_QUEUE_SIZE; ++i) {
        if (eventsToSimulate <= 0) break;
        Customer* cust = new Customer();

        cust->setArrivalTime(nextArrivalTime);
        cust->setEventStatus(ARRIVAL);

        pQueue.enqueue(cust);
        nextArrivalTime += model.getNextRandomInterval(lambda);

        --eventsToSimulate;
    }
}

void SimulationController::processNextEvent() {
    // Highest priority customer from priority queue
    Customer* cust = pQueue.dequeue();

    // Calculate time since the last event
    float timeSincePrevEvent = cust->getEventTime() - currTime;

    // Total number of customers in the system
    int customersInSystem = (numServiceChannels - serverAvailableCnt) + fQueue.getSize();

    // Number of customers in the queue
    int customersInQueue = fQueue.getSize();

    // Update total time-weighted number of customers in the system
    totalCustomerTimeInSystem += customersInSystem * timeSincePrevEvent;

    // Update total time-weighted number of customers in the queue
    totalCustomerTimeInQueue += customersInQueue * timeSincePrevEvent;

    // Update the current time to the time of this event
    currTime = cust->getEventTime();

    if (cust->getEventStatus() == ARRIVAL) {
        if (serverAvailableCnt > 0) {
            // Decrement the number of available servers
            --serverAvailableCnt;

            // Set service start time and calculated departure time
            cust->setStartOfServiceTime(cust->getArrivalTime());
            float departureInterval = model.getNextRandomInterval(mu);
            cust->setDepartureTime(cust->getArrivalTime() + departureInterval);

            // Sets the future event status to departure
            cust->setEventStatus(DEPARTURE);

            // Returns the customer with their new event status to the priority queue
            pQueue.enqueue(cust);
        } else {
            fQueue.enqueue(cust);
        }
    } else if (cust->getEventStatus() == DEPARTURE) {
        // Increment the number of available servers
        ++serverAvailableCnt;

        processStatistics(cust);

        if (fQueue.getFront() != nullptr) {
            // Next customer from fifo queue
            Customer* temp = fQueue.dequeue();

            // Set service start time and calculated departure time
            temp->setStartOfServiceTime(cust->getDepartureTime());
            float departureInterval = model.getNextRandomInterval(mu);
            temp->setDepartureTime(temp->getArrivalTime() + departureInterval);

            // Sets the future event status to departure
            temp->setEventStatus(DEPARTURE);

            // Returns the customer with their new event status to the priority queue
            pQueue.enqueue(temp);

            // Decrement the number of available servers
            --serverAvailableCnt;
        }
        
        // Records the final departure time
        // Slightly inefficient since it will run multiple times in the last batch of arrivals
        if (eventsToSimulate <= 0) {
            lastDepartureTime = cust->getDepartureTime();
        }
    } else {
        throw std::runtime_error("Invalid Event Flag");
    }
}

void SimulationController::runSimulation(std::string filename) {
    std::cout << "Running " << filename << " simulation..." << std::endl;

    loadModel(filename);

    addArrivals();
    serverAvailableCnt = numServiceChannels;

    while (pQueue.getSize() > 0) {
        processNextEvent();

        if (eventsToSimulate > 0 && pQueue.getSize() <= numServiceChannels + 1) {
            addArrivals();
        }
    }

    std::cout << "Simulation complete. Printing results..." << std::endl;

    printStatistics();

    clearVariables();
}
