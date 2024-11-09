/***************************************************************
  Student Name: Sarah Wallis
  File Name: packing-controller.hpp
  Assignment number: Project 4

  Class for managing bin packing algorithms
***************************************************************/
#include <vector>
#include "./bin-container.hpp"

class PackingController {
    private:
        // Struct for containing references to constants
        // Used for index access in binContainers vector for improved readability
        struct {
            const int OPTIMAL_FIT = 0;
            const int ONLINE_FIRST_FIT = 1;
            const int ONLINE_NEXT_FIT = 2;
            const int ONLINE_BEST_FIT = 3;
            const int OFFLINE_FIRST_FIT = 4;
            const int OFFLINE_BEST_FIT = 5;
            const int NUMBER_OF_TYPES = 6;
        };
        std::vector<BinContainer> binContainers; // Stores the bin containers for each algorithm
        std::vector<double> items; // Stores the list of items for packing
        double maxBinCapacity;
        void insertionSort(std::vector<double>& s); // Basic sorting algorithm for offline algorithms
        void swap(int p, int q, std::vector<int>& s); // In place vector swap method
        void incrementPermutation(std::vector<int>& s); // Increments int permutations in lexographical order
        void printS(std::vector<double>& s); // Prints out a list of doubles in order
        size_t computeFactorial(size_t num); // Recursive factorial algorithm
        void computeOptimalFit(); // Brute force optimal fit algorithm
        void computeFirstFit(int algoType, std::vector<double> itemsList); // First fit bin packing algorithm
        void computeNextFit(int algoType, std::vector<double> itemsList); // Next fit bin packing algorithm
        void computeBestFit(int algoType, std::vector<double> itemsList); // Best fit bin packing algorithm
    public:
        PackingController(std::vector<double> items, double maxBinCapacity);
        void runPackingSimulations(); // Runs all algorithms
        void print(); // Prints results to console
};