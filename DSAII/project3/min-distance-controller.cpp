#include "./min-distance-controller.hpp"
#include <cmath>
#include <cstddef>

MinDistanceController::MinDistanceController(int numCities, std::string distancesFile) {
    this->numCities = numCities;
    optimalCost = INFINITY;
    geneticCost = INFINITY;
    
    cityWeights = CityMatrix(numCities, distancesFile);
    elite = std::vector<int>(numCities);
    bestPermutation = std::vector<int>(numCities);
}

void MinDistanceController::calculateCostBruteForce() {
    auto start_time = std::chrono::high_resolution_clock::now();

    size_t numComputations = cityWeights.computeFactorial(numCities - 1); // No need to check different start points, thus minus 1
    std::vector<int> perm;
    double tempCost;

    for (size_t i = 1; i < numComputations; ++i) {
        perm = cityWeights.getNextPerm();
        tempCost = 0.0;

        for (int j = 1; j < numCities; ++j) {
            tempCost += cityWeights.getValue(perm[j - 1], perm[j]);
        }

        // Adds return to start to calculated cost
        tempCost += cityWeights.getValue(perm[numCities - 1], perm[0]);

        if (tempCost < optimalCost) {
            optimalCost = tempCost;
            bestPermutation = perm;
            bestPermutation.push_back(bestPermutation[0]);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    bruteForceTime = end_time - start_time;
}

// int* MinDistanceController::calculateCostGenetic() {

// }

void MinDistanceController::displayResults() {
    if (optimalCost == INFINITY) {
        std::cout << "No solution found." << std::endl;
        return;
    }

    std::cout << "Optimal Permutation: ";
    cityWeights.printS(bestPermutation);

    std::cout << "Optimal cost: " << optimalCost << std::endl;
    std::cout << "Brute force algorithm time: " << bruteForceTime.count() << "s" << std::endl;
}

void MinDistanceController::runCalculations() {
    calculateCostBruteForce();
    displayResults();
}