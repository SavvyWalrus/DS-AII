/***************************************************************
  Student Name: Sarah Wallis
  File Name: packing-controller.hpp
  Assignment number: Project 4

  Class for managing bin packing algorithms
***************************************************************/
#include <cstddef>
#include <vector>
#include "./bin-container.hpp"

class PackingController {
    private:
        // Enum for containing references to constants
        // Used for index access in binContainers vector for improved readability
        enum {
            OPTIMAL_FIT = 0,
            ONLINE_FIRST_FIT = 1,
            ONLINE_NEXT_FIT = 2,
            ONLINE_BEST_FIT = 3,
            OFFLINE_FIRST_FIT = 4,
            OFFLINE_BEST_FIT = 5,
            NUMBER_OF_TYPES = 6,
        };
        std::vector<BinContainer> binContainers; // Stores the bin containers for each algorithm
        std::vector<double> items; // Stores the list of items for packing
        void insertionSort(std::vector<double>& s); // Basic sorting algorithm for offline algorithms
        void swap(int p, int q, int s[]); // In place int swap method
        void incrementPermutation(int s[], int size); // Increments int permutations in lexicographical order
        bool skipToNextPermutation(int arr[], int size, int indexToIncrement); // Skips all lexicographical permutations for indeces following indexPos
        void printS(int s[], int size); // Prints out a list of int in current order
        size_t computeFactorial(size_t num); // Recursive factorial algorithm
        void computeOptimalFit(); // Brute force optimal fit algorithm
        void computeFirstFit(int algoType, std::vector<double> itemsList); // First fit bin packing algorithm
        void computeNextFit(int algoType, std::vector<double> itemsList); // Next fit bin packing algorithm
        void computeBestFit(int algoType, std::vector<double> itemsList); // Best fit bin packing algorithm
    public:
        PackingController(std::vector<double> items);
        void runPackingSimulations(); // Runs all algorithms
        void print(); // Prints results to console
};