#include "./min-distance-controller.hpp"
#include <iostream>

int main() {
    int numCities, numTours, numGenerations, percentageMutations;

    std::cout << "Enter the number of cities to run [10-20]: ";
    std::cin >> numCities;
    // std::cout << "Enter the number of tours per generation: ";
    // std::cout << "Enter the number of generations to run: ";
    // std::cout << "Enter the percentage of a generation's mutations (0-100]: ";


    MinDistanceController controller = MinDistanceController(numCities, "./distances.txt");
    controller.runCalculations();

    return 0;
}