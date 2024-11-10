/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin-container.cpp
  Assignment number: Project 4

  Class for managing bin containers
***************************************************************/
#include "./bin-container.hpp"
#include <iomanip>
#include <iostream>

BinContainer::BinContainer() {
    maxBinCapacity = -1;
    binCount = 0;
}

BinContainer::BinContainer(int maxBinCapacity) {
    this->maxBinCapacity = maxBinCapacity;
    binCount = 0;
}

int BinContainer::getBinCount() {
    return binCount;
}

Bin& BinContainer::getBinAt(size_t index) {
    // Returns new empty bin as failsafe
    if (binCount <= index) {
        addNewEmptyBin();
        return bins.back();
    } else {
        return bins.at(index);
    }
}

Bin& BinContainer::getLastBin() {
    // Initializes new bin if none present
    if (binCount == 0 && bins.size() == 0) {
        addNewEmptyBin();
    }
    return bins.at(binCount - 1);
}

void BinContainer::addNewEmptyBin() {
    if (bins.size() <= binCount) {
        Bin newBin = Bin(maxBinCapacity);
        bins.push_back(newBin);
    } else {
        bins.at(binCount).clear();
    }

    ++binCount;
}

void BinContainer::print() {
    for (size_t i = 0; i < bins.size(); ++i) {
        std::cout << "  b" << i+1 << ": " << std::setprecision(3) << std::fixed; // Assumes no item more precise than three decimal places
        for (auto item : bins.at(i).getItems()) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

void BinContainer::clear() {
    int numBins = getBinCount();

    for (int i = 0; i < numBins; ++i) {
        bins.at(i).clear();
    }
}
