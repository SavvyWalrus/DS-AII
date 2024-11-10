/***************************************************************
  Student Name: Sarah Wallis
  File Name: packing-controller.cpp
  Assignment number: Project 4

  Class for managing bin packing algorithms
***************************************************************/
#include "./packing-controller.hpp"
#include <cstddef>
#include <iomanip>
#include <ios>
#include <vector>
#include <iostream>
#include <chrono>

PackingController::PackingController(std::vector<double> items) {
    this->items = items;
    binContainers = std::vector<BinContainer>(NUMBER_OF_TYPES);
}

// Straightforward insertion sort for sorting from largest to smallest
void PackingController::insertionSort(std::vector<double>& s) {
    size_t size = s.size();

    for (size_t i = 1; i < size; ++i) {
        double key = s.at(i);
        int j = i - 1;

        while (j >= 0 && s.at(j) < key) {
            s.at(j+1) = s.at(j);
            --j;
        }
        s.at(j+1) = key;
    }
}

// Swaps items in place
void PackingController::swap(int p, int q, int s[]) {
    int temp = s[p];
    s[p] = s[q];
    s[q] = temp;
}

// Renamed perm1() method
void PackingController::incrementPermutation(int s[], int size) {
    int m, k, p, q;

    m = size - 2;
    while (s[m] > s[m + 1]) {
        m = m - 1;
    }

    k = size - 1;
    while (s[m] > s[k]) {
        k = k - 1;
    }

    swap(m, k, s);

    p = m + 1;
    q = size - 1;
    while (p < q) {
        swap(p, q, s);
        ++p;
        --q;
    }

    // printS(s, size);
}

// Prints int array entries in order
void PackingController::printS(int s[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        std::cout << s[i] << " -> ";
    }
    std::cout << s[size - 1] << std::endl;
}

// Recursive factorial function
size_t PackingController::computeFactorial(size_t num) {
    if (num <= 1) {
        return 1;
    } else {
        return num * computeFactorial(num - 1);
    }
}

void PackingController::computeOptimalFit() {
    std::cout << "Starting optimal packing algorithm..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    int indeces[MAX_NUM_BINS]; // An array for storing index representations for permutations ; Needed to avoid permutation failures on duplicate values
    size_t numPermutations = computeFactorial(items.size() - 1); // No need to check different first item, thus minus 1
    int numOfItems = items.size();
    int bestBinCount = 0;
    binContainers.at(OPTIMAL_FIT) = BinContainer();

    // Store a list of int indeces for permutation swapping
    for (int i = 0; i < numOfItems; ++i) {
        indeces[i] = i;
    }

    BinContainer container = BinContainer();
    std::cout << "Permutations to calculate: " << numPermutations << "\nThis may take a while..." << std::endl;

    // Computes next fit for each permutation
    for (size_t i = 1; i < numPermutations; ++i) {
        // Inserts each item into a bin using next fit
        for (int j = 0; j < numOfItems; ++j) {
            container.addNewItemByNextFit(items[indeces[j]]);
        }

        // Checks for new optimal bin count
        if (container.getBinCount() < bestBinCount || bestBinCount == 0) {
            binContainers.at(OPTIMAL_FIT) = container;
            bestBinCount = binContainers.at(OPTIMAL_FIT).getBinCount();
        }

        container.clear();

        // Increments the permutation of int indeces
        incrementPermutation(indeces, numOfItems);

        if (i % 10000000 == 0) {
            std::cout << "Permutation " << i << "..." << std::endl;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = end_time - start_time;
    std::cout << "Algorithm finished\nTotal elapsed time for optimal algorithm: " << totalTime.count() << "s" << std::endl;
}

void PackingController::computeFirstFit(int algoType, std::vector<double> itemsList) {
    BinContainer container = BinContainer();

    for (auto item : itemsList) {
        container.addNewItemByFirstFit(item);
    }

    binContainers.at(algoType) = container;
}

void PackingController::computeNextFit(int algoType, std::vector<double> itemsList) {
    BinContainer container = BinContainer();

    for (auto item : itemsList) {
        container.addNewItemByNextFit(item);
    }

    binContainers.at(algoType) = container;
}

void PackingController::computeBestFit(int algoType, std::vector<double> itemsList) {
    BinContainer container = BinContainer();
    double bestFitFullness;
    double currFitFullness;
    int bestBinIndex;
    int binCount;

    for (auto item : itemsList) {
        binCount = container.getBinCount();

        if (binCount == 0) {
            container.addNewItemByNextFit(item);
            continue;
        }

        bestFitFullness = 0;
        bestBinIndex = binCount;

        // Finds the best fit for the current item
        for (int i = 0; i < binCount; ++i) {
            currFitFullness = container.getBinAt(i).getFillAmount() + item;
            if (currFitFullness <= MAX_BIN_CAPACITY && currFitFullness > bestFitFullness) {
                bestFitFullness = currFitFullness;
                bestBinIndex = i;
            }
        }

        // Inserts the item at the found best bin index
        // If no fit is found, a new bin will be added--triggered by bestBinIndex being equal to binCount
        container.getBinAt(bestBinIndex).tryAddItem(item);
    }

    binContainers.at(algoType) = container;
}

void PackingController::runPackingSimulations() {
    std::vector<double> itemsSorted = items;
    insertionSort(itemsSorted);

    computeOptimalFit();
    computeFirstFit(ONLINE_FIRST_FIT, items);
    computeNextFit(ONLINE_NEXT_FIT, items);
    computeBestFit(ONLINE_BEST_FIT, items);
    computeFirstFit(OFFLINE_FIRST_FIT, itemsSorted);
    computeBestFit(OFFLINE_BEST_FIT, itemsSorted);
}

void PackingController::print() {
    // Outputs results table
    std::cout << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::setw(37) << std::left << "|      Policy     | Total Bins Used |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|Optimal Solution |" << std::right << std::setw(7) << binContainers.at(OPTIMAL_FIT).getBinCount() << " bins     |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|Online Algorithm |" << std::right << std::setw(18) << "|" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|  First Fit      |" << std::right << std::setw(7) << binContainers.at(ONLINE_FIRST_FIT).getBinCount() << " bins     |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|  Next Fit       |" << std::right << std::setw(7) << binContainers.at(ONLINE_NEXT_FIT).getBinCount() << " bins     |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|  Best Fit       |" << std::right << std::setw(7) << binContainers.at(ONLINE_BEST_FIT).getBinCount() << " bins     |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|Offline Algorithm|" << std::right << std::setw(18) << "|" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|  First Fit      |" << std::right << std::setw(7) << binContainers.at(OFFLINE_FIRST_FIT).getBinCount() << " bins     |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::left << "|  Best Fit       |" << std::right << std::setw(7) << binContainers.at(OFFLINE_BEST_FIT).getBinCount() << " bins     |" << std::endl;
    std::cout << std::setw(37) << std::setw(37) << std::setfill('-') << "" << std::endl << std::setfill(' ');
    std::cout << std::endl;

    // Outputs the packing of each method's bin container
    std::cout << "Optimal: " << std::endl;
    binContainers.at(OPTIMAL_FIT).print();
    std::cout << "Online First Fit: " << std::endl;
    binContainers.at(ONLINE_FIRST_FIT).print();
    std::cout << "Online Next Fit: " << std::endl;
    binContainers.at(ONLINE_NEXT_FIT).print();
    std::cout << "Online Best Fit: " << std::endl;
    binContainers.at(ONLINE_BEST_FIT).print();
    std::cout << "Offline First Fit: " << std::endl;
    binContainers.at(OFFLINE_FIRST_FIT).print();
    std::cout << "Offline Best Fit: " << std::endl;
    binContainers.at(OFFLINE_BEST_FIT).print();
}
