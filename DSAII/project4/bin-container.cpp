/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin-container.cpp
  Assignment number: Project 4

  Class for managing bin containers
***************************************************************/
#include "./bin-container.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

BinContainer::BinContainer() {
    binCount = 0;
}

int BinContainer::getBinCount() {
    return binCount;
}

Bin& BinContainer::getBinAt(int index) {
    // Returns new empty bin as failsafe
    if (binCount <= index) {
        addNewEmptyBin();
        return bins[binCount - 1];
    } else {
        return bins[index];
    }
}

Bin& BinContainer::getLastBin() {
    // Initializes new bin if none present
    if (binCount == 0) addNewEmptyBin();
    return bins[binCount - 1];
}

void BinContainer::addNewEmptyBin() {
    bins[binCount].clear();
    ++binCount;
}

void BinContainer::addNewItemByNextFit(double item) {
    if (!getLastBin().tryAddItem(item)) {
        addNewEmptyBin();
        getLastBin().tryAddItem(item);
    }
}

void BinContainer::addNewItemByFirstFit(double item) {
    bool added = false;

    for (int i = 0; i <= binCount; ++i) {
        if (getBinAt(i).tryAddItem(item)) {
            added = true;
            break;
        }
    }

    if (!added) {
        addNewItemByNextFit(item);
    } else {
        added = false;
    }
}

void BinContainer::print() {
    for (int i = 0; i < binCount; ++i) {
        std::vector<double> items = bins[i].getItems();
        std::cout << "  b" << i+1 << ": " << std::setprecision(3) << std::fixed; // Assumes no item more precise than three decimal places
        for (auto item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

void BinContainer::clear() {
    binCount = 0;
}
