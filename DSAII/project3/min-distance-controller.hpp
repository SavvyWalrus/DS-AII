/***************************************************************
  Student Name: Sarah Wallis
  File Name: min-distance-controller.hpp
  Assignment number: Project 3

  Controller for both algorithm types and results output
***************************************************************/
#ifndef MIN_DISTANCE_CONTROLLER
#define MIN_DISTANCE_CONTROLLER
#include "./city-matrix.hpp"
#include <chrono>
#include <unordered_map>
#include <vector>

/**
Vector hash function taken from StackOverflow
Used for memoization
https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector/72073933#72073933
**/
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
        CityMatrix cityWeights; // Adjacency matrix
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

        // Used for permutation memoization (Unfortunately slightly slower with number of generations used as the termination condition).
        // Kept in since it could be optimized, but program works fine with or without it.
        std::unordered_map<std::vector<int>, double, VectorHash> fitnessCache;

        double getFitness(std::vector<int> perm);
        void calculateCostBruteForce(); // Brute force algorithm
        void calculateCostGenetic(); // Genetic algorithm
        void displayResults();
    public:
        MinDistanceController(int numCities, int numToursPerGeneration, int generationsToRun, int percentageMutations, std::string distancesFile);
        void runCalculations();
};

#endif