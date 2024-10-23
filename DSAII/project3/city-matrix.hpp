#ifndef CITY_MATRIX
#define CITY_MATRIX
#include "./two-d-array.hpp"
#include <vector>
#define NUMELEMENTS 20

class CityMatrix {
    private:
        int numCities;
        std::vector<int> currPerm;
        std::vector<int> basePerm;
        TwoDArray<double> cityWeights;
        void swap(int p, int q, std::vector<int>& s);
    public:
        CityMatrix();
        CityMatrix(int numCities, std::string distancesFile);
        size_t computeFactorial(size_t num);
        void perm1(std::vector<int>& s);
        void setNumCities(int numCities);
        void printS(std::vector<int> s);
        std::vector<int> getNextPerm();
        std::vector<int> getBasePerm();
        double getValue(int i, int j);
};

#endif