#include "./math-model.hpp"
#include <stdexcept>
#include <cmath>

float MathModel::getLambda() {
    return lambda;
}

void MathModel::setLambda(float value) {
    this->lambda = value;
}

float MathModel::getMu() {
    return mu;
}

void MathModel::setMu(float value) {
    this->mu = value;
}

int MathModel::getNumServiceChannels() {
    return numServiceChannels;
}

void MathModel::setNumServiceChannels(int value) {
    this->numServiceChannels = value;
}

int MathModel::computeFactorial(int value) {
    if (value < 0) throw std::runtime_error("Error: Invalid value for factorial");
    if (value == 0) return 1;
    int sum = value;
    int i = value - 1;

    while (i > 0) {
        sum *= i;
        --i;
    }

    return sum;
}

float MathModel::calcIdleTime() {
    float summation = 0;
    float a, b, c;

    for (int i = 0; i < numServiceChannels; ++i) {
        a = 1.0 / computeFactorial(i);
        b = pow((lambda / mu), i);
        summation += a * b;
    }

    a = 1.0 / computeFactorial(numServiceChannels);
    b = pow((lambda / mu), numServiceChannels);
    c = numServiceChannels * mu / (numServiceChannels * mu - lambda);

    summation += a * b * c;

    return (1.0 / summation);
}

float MathModel::calcAvgNumPeople() {
    float numerator, denominator, result;

    numerator = lambda * mu * (pow((lambda / mu), numServiceChannels));
    denominator = computeFactorial(numServiceChannels - 1) * pow((numServiceChannels * mu - lambda), 2);

    result = (numerator / denominator) * idleTime + (lambda / mu);

    return result;
}

float MathModel::calcAvgTotalTime() {
    return (avgNumPeople / lambda);
}

float MathModel::calcAvgQueueNum() {
    return (avgNumPeople - (lambda / mu));
}

float MathModel::calcAvgTimeInQueue() {
    return (avgQueueNum / lambda);
}

float MathModel::calcUtilization() {
    return (lambda / (numServiceChannels * mu));
}

void MathModel::calculateNewValues(float lambda, float mu, int numServiceChannels) {
    this->lambda = lambda;
    this->mu = mu;
    this->numServiceChannels = numServiceChannels;

    idleTime = calcIdleTime();
    avgNumPeople = calcAvgNumPeople();
    avgTotalTime = calcAvgTotalTime();
    avgQueueNum = calcAvgQueueNum();
    avgTimeInQueue = calcAvgTimeInQueue();
    utilization = calcUtilization();
}

float MathModel::getIdleTime() {
    return idleTime;
}

float MathModel::getAvgNumPeople() {
    return avgNumPeople;
}

float MathModel::getAvgTotalTime() {
    return avgTotalTime;
}

float MathModel::getAvgQueueNum() {
    return avgQueueNum;
}

float MathModel::getAvgTimeInQueue() {
    return avgTimeInQueue;
}

float MathModel::getUtilization() {
    return utilization;
}

float MathModel::getNextRandomInterval(float avg) {
    float f = 0.0;

    // Excludes 0 from possible results
    while (f == 0.0) {
        f = (float)rand()/(float)(RAND_MAX);
    }

    float intervalTime = -1 * (1.0 / avg) * log(f);
    return intervalTime;
}

MathModel::MathModel(float lambda, float mu, int numServiceChannels) {
    calculateNewValues(lambda, mu, numServiceChannels);
}

MathModel::MathModel() {
    setLambda(0);
    setMu(0);
    setNumServiceChannels(0);
}
