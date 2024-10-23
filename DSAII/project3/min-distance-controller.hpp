#ifndef MIN_DISTANCE_CONTROLLER
#define MIN_DISTANCE_CONTROLLER
#include "./city-matrix.hpp"
#include <chrono>
#include <vector>

class MinDistanceController {
    private:
        CityMatrix cityWeights;
        std::vector<int> elite;
        std::vector<int> optimalPerm;
        int numCities;
        int numToursPerGeneration;
        int generationsToRun;
        int percentageMutations;
        double optimalCost;
        double geneticCost;
        std::chrono::duration<double> bruteForceTime;
        std::chrono::duration<double> geneticTime;

        double getFitness(std::vector<int> perm);
        void calculateCostBruteForce();
        void calculateCostGenetic();
        void displayResults();
    public:
        MinDistanceController(int numCities, int numToursPerGeneration, int generationsToRun, int percentageMutations, std::string distancesFile);
        void runCalculations();
};

#endif