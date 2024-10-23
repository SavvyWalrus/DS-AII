#include "./min-distance-controller.hpp"
#include <cmath>
#include <cstddef>
#include <vector>
#include <iomanip>

MinDistanceController::MinDistanceController(int numCities, int numToursPerGeneration, int generationsToRun, int percentageMutations, std::string distancesFile) {
    this->numCities = numCities;
    this->numToursPerGeneration = numToursPerGeneration;
    this->generationsToRun = generationsToRun;
    this->percentageMutations = percentageMutations;
    optimalCost = INFINITY;
    geneticCost = INFINITY;
    
    cityWeights = CityMatrix(numCities, distancesFile);
    elite = std::vector<int>(numCities);
    optimalPerm = std::vector<int>(numCities);
}

void MinDistanceController::calculateCostBruteForce() {
    auto start_time = std::chrono::high_resolution_clock::now();

    size_t numComputations = cityWeights.computeFactorial(numCities - 1); // No need to check different start points, thus minus 1
    std::vector<int> perm;
    double tempCost;

    for (size_t i = 1; i < numComputations; ++i) {
        perm = cityWeights.getNextPerm();
        tempCost = getFitness(perm);

        if (tempCost < optimalCost) {
            optimalCost = tempCost;
            optimalPerm = perm;
            optimalPerm.push_back(optimalPerm[0]);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    bruteForceTime = end_time - start_time;
}

void MinDistanceController::calculateCostGenetic() {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> currentGeneration;
    elite = cityWeights.getNextPerm();
    geneticCost = getFitness(elite);
    double tempCost;
    int randomMutation;

    // Generate random population for first generation
    for (int i = 0; i < numToursPerGeneration; ++i) {
        currentGeneration.push_back(cityWeights.getRandomPerm(elite));
    }

    while (generationsToRun > 0) {
        for (auto perm : currentGeneration) {
            tempCost = getFitness(perm);
            if (tempCost < geneticCost) {
                geneticCost = tempCost;
                elite = perm;
            }
        }

        for (auto perm : currentGeneration) {
            randomMutation = rand() % 100;
            if (randomMutation < percentageMutations) {
                perm = elite;
                cityWeights.mutatePerm(perm);
            } else {
                perm = cityWeights.attemptCrossoverPerm(perm, elite);
            }
        }

        --generationsToRun;
    }

    elite.push_back(elite[0]);

    auto end_time = std::chrono::high_resolution_clock::now();
    geneticTime = end_time - start_time;
}

double MinDistanceController::getFitness(std::vector<int> perm) {
    double tempCost = 0.0;

    for (int i = 1; i < numCities; ++i) {
        tempCost += cityWeights.getValue(perm[i - 1], perm[i]);
    }

    // Adds return to start to calculated cost
    tempCost += cityWeights.getValue(perm[numCities - 1], perm[0]);

    return tempCost;
}

void MinDistanceController::displayResults() {
    std::cout << "\nRESULTS" << std::endl;
    std::cout << std::setw(30) << std::setfill('-') << "" << std::endl << std::setfill(' ');

    if (optimalCost == INFINITY) {
        std::cout << "No solution found." << std::endl;
        return;
    }

    std::cout << "Number of cities run: " << numCities << std::endl;
    
    std::cout << "Optimal permutation: ";
    cityWeights.printS(optimalPerm);
    std::cout << "Optimal cost: " << optimalCost << std::endl;
    std::cout << "Brute force algorithm time: " << bruteForceTime.count() << "s\n" << std::endl;
    
    std::cout << "Best genetic permutation: ";
    cityWeights.printS(elite);
    std::cout << "Genetic cost: " << geneticCost << std::endl;
    std::cout << "Genetic algorithm time: " << geneticTime.count() << "s" << std::endl;
    std::cout << "Successful crossovers: " << cityWeights.getSuccessfulCrossovers() << std::endl;
    std::cout << "Percent of optimal cost: " << geneticCost / optimalCost * 100 << "%" << std::endl;
}

void MinDistanceController::runCalculations() {
    calculateCostBruteForce();
    calculateCostGenetic();
    displayResults();
}