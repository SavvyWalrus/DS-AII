#ifndef MIN_DISTANCE_CONTROLLER
#define MIN_DISTANCE_CONTROLLER
#include "./city-matrix.hpp"
#include <chrono>
#include <vector>

class MinDistanceController {
    private:
        CityMatrix cityWeights;
        std::vector<int> elite;
        std::vector<int> basePermutation;
        std::vector<int> bestPermutation;
        int numCities;
        double optimalCost;
        double geneticCost;
        std::chrono::duration<double> bruteForceTime;
        std::chrono::duration<double> geneticTime;

        void calculateCostBruteForce();
        // int* calculateCostGenetic();
        void displayResults();
    public:
        MinDistanceController(int numCities, std::string distancesFile);
        void runCalculations();
};

#endif