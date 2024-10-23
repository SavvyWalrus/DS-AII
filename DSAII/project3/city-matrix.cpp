#include "./city-matrix.hpp"
#include "./two-d-array.hpp"
#include <cstddef>
#include <fstream>

CityMatrix::CityMatrix()
: cityWeights(0, 0, 0.0) {
    numCities = 0;
    currPerm = std::vector<int>(0);
    basePerm = std::vector<int>(0);
}

CityMatrix::CityMatrix(int numCities, std::string distancesFile) {
    this->numCities = numCities;
    cityWeights = TwoDArray<double>(NUMELEMENTS, NUMELEMENTS, 0.0);
    currPerm = std::vector<int>(numCities);
    basePerm = std::vector<int>(numCities);
    
    // Assigns city number values for permutation representation
    for (int i = 0; i < numCities; ++i) {
        currPerm[i] = i;
        basePerm[i] = i;
    }

    std::ifstream file(distancesFile);
    
    if (!file.is_open()) {
        std::cerr << "There was a problem opening the input file!\n";
        exit(1);
    }

    double temp;

    for (int i = 0; i < NUMELEMENTS; ++i) {
        for (int j = 0; j < NUMELEMENTS; ++j) {
            if (i == j) {
                continue;
            } else if (file >> temp) {
                cityWeights.setValue(i, j, temp);
            } else {
                std::cerr << "Insufficient number of weights in input file!\n";
                exit(1);
            }
        }
    }

    file.close();
}

void CityMatrix::swap(int p, int q, std::vector<int>& s) {
    int temp = s[p];
    s[p] = s[q];
    s[q] = temp;
}

// For calculating the number of computations
size_t CityMatrix::computeFactorial(size_t num) {
    if (num == 0) return 1;

    int temp = 1;

    for (int i = num; i > 0; --i) {
        temp *= i;
    }

    return temp;
}

void CityMatrix::perm1(std::vector<int>& s) {
    int m, k, p , q;

    m = numCities-2;
    while(s[m]>s[m+1]) {
        m = m - 1;
    }

    k = numCities-1;
    while(s[m] > s[k]) {
        k = k - 1;
    }

    swap(m, k, s);
    
    p = m + 1;
    q = numCities - 1;
    while( p < q) {
        swap(p, q, s);
        ++p;
        --q;
    }

    currPerm = s;
    // printS(s);
}

void CityMatrix::setNumCities(int numCities) {
    this->numCities = numCities;
}

void CityMatrix::printS(std::vector<int> s) {
    if (!numCities) {
        std::cerr << "Number of cities has not been initialized!\n";
        exit(1);
    }

    for (size_t i = 0; i < s.size() - 1; ++i) {
        std::cout << s[i] << " -> ";
    }

    std::cout << s[s.size() - 1] << std::endl;
}

std::vector<int> CityMatrix::getNextPerm() {
    std::vector<int> tempPerm(numCities);

    for (int i = 0; i < numCities; ++i) {
        tempPerm[i] = currPerm[i];
    }

    perm1(this->currPerm);

    return tempPerm;
}

double CityMatrix::getValue(int i, int j) {
    return cityWeights.getValue(i, j);
}

std::vector<int> CityMatrix::getBasePerm() {
    return basePerm;
}