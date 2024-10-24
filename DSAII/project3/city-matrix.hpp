/***************************************************************
  Student Name: Sarah Wallis
  File Name: city-matrix.hpp
  Assignment number: Project 3

  Class for managing adjacency matrix and subsidiary algorithmic functions
***************************************************************/
#ifndef CITY_MATRIX
#define CITY_MATRIX
#include "./two-d-array.hpp"
#include <vector>
#define NUMELEMENTS 20

class CityMatrix {
    private:
        int numCities;
        int successfulCrossovers; // Used for debugging and testing crossover algorithm
        std::vector<int> currPerm;
        TwoDArray<double> cityWeights; // City connection weight adjacency matrix
        void swap(int p, int q, std::vector<int>& s); // In place swapping algorithm
    public:
        CityMatrix(); // Default constructor
        CityMatrix(int numCities, std::string distancesFile); // Paramerterized constructor
        size_t computeFactorial(size_t num); // Naive factorial algorithm
        void inrementPermutation(std::vector<int>& s); // In place increment to next permutation in lexicographical order
        std::vector<int> getRandomPerm(std::vector<int> s); // Returns a random permutation with 0th city in first index
        std::vector<int> mutatePerm(std::vector<int> s); // Returns a mutated permutation with random swaps, excluding first (0th) city
        std::vector<int> attemptCrossoverPerm(std::vector<int> s, std::vector<int> currElite); // Returns a permutation which combines the first half of one with the second half of the other. Defaults to mutation in fail cases.
        void printS(std::vector<int> s); // Prints a permutation with formatting
        std::vector<int> getNextPerm();
        void setNumCities(int numCities);
        double getValue(int i, int j); // Returns the weight connecting cities i and j
        int getSuccessfulCrossovers(); // Returns total number of successful crossovers
};

#endif