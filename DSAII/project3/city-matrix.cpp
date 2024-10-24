#include "./city-matrix.hpp"
#include "./two-d-array.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <set>

CityMatrix::CityMatrix()
: cityWeights(0, 0, 0.0) {
    numCities = 0;
    currPerm = std::vector<int>(0);
}

CityMatrix::CityMatrix(int numCities, std::string distancesFile) {
    this->numCities = numCities;
    successfulCrossovers = 0;
    cityWeights = TwoDArray<double>(NUMELEMENTS, NUMELEMENTS, 0.0);
    currPerm = std::vector<int>(numCities);
    
    // Assigns city number values for permutation representation
    for (int i = 0; i < numCities; ++i) {
        currPerm[i] = i;
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

void CityMatrix::inrementPermutation(std::vector<int>& s) {
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

std::vector<int> CityMatrix::getRandomPerm(std::vector<int> s) {
    std::random_shuffle(s.begin() + 1, s.end());
    return s;
}

std::vector<int> CityMatrix::mutatePerm(std::vector<int> s) {
    if (s.size() <= 2) return s;

    int numMutations = rand() % (numCities / 2);
    int firstIndex;
    int secondIndex;

    for (int i = 0; i < numMutations; ++i) {
        firstIndex = (rand() % (numCities - 1)) + 1;
        do {
            secondIndex = (rand() % (numCities - 1)) + 1;
        } while (secondIndex == firstIndex);
        swap(firstIndex, secondIndex, s);
    }

    return s;
}

std::vector<int> CityMatrix::attemptCrossoverPerm(std::vector<int> s, std::vector<int> currElite) {
    std::set<int> sHalf;
    std::set<int> eliteHalf;

    for (size_t i = 0; i < s.size() / 2; ++i) {
        sHalf.insert(s[i]);
        eliteHalf.insert(currElite[i]);
    }

    // Performs mutation as backup
    if (sHalf != eliteHalf) {
        return mutatePerm(s);
    }
    
    int randomHalf = rand() % 2;

    if (randomHalf == 0) {
        for (size_t i = 0; i < s.size() / 2; ++i) {
            s[i] = currElite[i];
        }
    } else {
        for (size_t i = s.size() / 2; i < s.size(); ++i) {
            s[i] = currElite[i];
        }
    }

    ++successfulCrossovers;
    return s;
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

    inrementPermutation(this->currPerm);

    return tempPerm;
}

double CityMatrix::getValue(int i, int j) {
    return cityWeights.getValue(i, j);
}

int CityMatrix::getSuccessfulCrossovers() {
    return successfulCrossovers;
}