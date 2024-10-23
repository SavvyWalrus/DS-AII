#ifndef CITY_MATRIX
#define CITY_MATRIX
#include "./two-d-array.hpp"
#include <vector>
#define NUMELEMENTS 20

class CityMatrix {
    private:
        int numCities;
        int successfulCrossovers;
        std::vector<int> currPerm;
        TwoDArray<double> cityWeights;
        void swap(int p, int q, std::vector<int>& s);
    public:
        CityMatrix();
        CityMatrix(int numCities, std::string distancesFile);
        size_t computeFactorial(size_t num);
        void inrementPermutation(std::vector<int>& s);
        std::vector<int> getRandomPerm(std::vector<int> s);
        std::vector<int> mutatePerm(std::vector<int> s);
        std::vector<int> attemptCrossoverPerm(std::vector<int> s, std::vector<int> currElite);
        void setNumCities(int numCities);
        void printS(std::vector<int> s);
        std::vector<int> getNextPerm();
        double getValue(int i, int j);
        int getSuccessfulCrossovers();
};

#endif