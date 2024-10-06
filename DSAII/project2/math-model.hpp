#ifndef MATH_MODEL_HPP
#define MATH_MODEL_HPP

class MathModel {
    private:
        float lambda;
        float mu;
        int numServiceChannels;

        float idleTime;
        float avgNumPeople;
        float avgTotalTime;
        float avgQueueNum;
        float avgTimeInQueue;
        float utilization;

        int computeFactorial(int value);
        float calcIdleTime();
        float calcAvgNumPeople();
        float calcAvgTotalTime();
        float calcAvgQueueNum();
        float calcAvgTimeInQueue();
        float calcUtilization();
    public:
        MathModel();
        MathModel(float lambda, float mu, int numServiceChannels);
        float getLambda();
        void setLambda(float value);
        float getMu();
        void setMu(float value);
        int getNumServiceChannels();
        void setNumServiceChannels(int value);

        float getIdleTime();
        float getAvgNumPeople();
        float getAvgTotalTime();
        float getAvgQueueNum();
        float getAvgTimeInQueue();
        float getUtilization();
        
        float getNextRandomInterval(float avg);
        void calculateNewValues(float lambda, float mu, int numServiceChannels);
};

#endif