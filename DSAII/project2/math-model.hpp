#ifndef MATH_MODEL_HPP
#define MATH_MODEL_HPP

class MathModel {
    private:
        // Statistical values
        float idleTime;
        float avgNumPeople;
        float avgTotalTime;
        float avgQueueNum;
        float avgTimeInQueue;
        float utilization;

        // Helper functions for computing statistics
        int computeFactorial(int value);
        float calcIdleTime(float lambda, float mu, float numServiceChannels);
        float calcAvgNumPeople(float lambda, float mu, float numServiceChannels);
        float calcAvgTotalTime(float lambda);
        float calcAvgQueueNum(float lambda, float mu);
        float calcAvgTimeInQueue(float lambda);
        float calcUtilization(float lambda, float mu, float numServiceChannels);
    public:
        // Default constructor
        MathModel();

        // Parameterized constructor
        MathModel(float lambda, float mu, float numServiceChannels);

        // Getters for precalculated statistical values
        float getIdleTime();
        float getAvgNumPeople();
        float getAvgTotalTime();
        float getAvgQueueNum();
        float getAvgTimeInQueue();
        float getUtilization();
        
        // Returns a float representing a random time interval
        float getNextRandomInterval(float avg);

        // Runs the statistical functions with the current variables
        void calculateNewValues(float lambda, float mu, float numServiceChannels);
};

#endif