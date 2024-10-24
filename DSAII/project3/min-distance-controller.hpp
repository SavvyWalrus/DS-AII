#ifndef MIN_DISTANCE_CONTROLLER
#define MIN_DISTANCE_CONTROLLER
#include "./city-matrix.hpp"
#include <chrono>
#include <unordered_map>
#include <vector>

// Vector hash function taken from StackOverflow
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector/72073933#72073933
struct VectorHash {
    std::size_t operator()(std::vector<int> const& vec) const {
        std::size_t seed = vec.size();
        for(auto x : vec) {
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = (x >> 16) ^ x;
            seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

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
        std::unordered_map<std::vector<int>, double, VectorHash> fitnessCache;

        double getFitness(std::vector<int> perm);
        void calculateCostBruteForce();
        void calculateCostGenetic();
        void displayResults();
    public:
        MinDistanceController(int numCities, int numToursPerGeneration, int generationsToRun, int percentageMutations, std::string distancesFile);
        void runCalculations();
};

#endif