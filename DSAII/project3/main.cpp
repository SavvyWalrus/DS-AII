/***************************************************************
  Student Name: Sarah Wallis
  File Name: main.cpp
  Assignment number: Project 3

  Main function for running program
***************************************************************/
#include "./min-distance-controller.hpp"
#include <iostream>

int main() {
    int numCities, numTours, numGenerations, percentageMutations;

    std::cout << "Enter the number of cities to run [10-20]: ";
    std::cin >> numCities;
    std::cout << "Enter the number of tours per generation: ";
    std::cin >> numTours;
    std::cout << "Enter the number of generations to run: ";
    std::cin >> numGenerations;
    std::cout << "Enter the percentage of a generation's mutations (0-100]: ";
    std::cin >> percentageMutations;


    MinDistanceController controller = MinDistanceController(numCities, numTours, numGenerations, percentageMutations, "./distances.txt");
    controller.runCalculations();

    return 0;
}