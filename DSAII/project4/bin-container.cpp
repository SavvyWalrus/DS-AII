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
}

BinContainer::BinContainer(int maxBinCapacity) {
    this->maxBinCapacity = maxBinCapacity;
}

int BinContainer::getBinCount() {
    return bins.size();
}

Bin& BinContainer::getBinAt(size_t index) {
    // Returns new empty bin as failsafe
    if (bins.size() <= index) {
        addNewEmptyBin();
        return bins.back();
    } else {
        return bins.at(index);
    }
}

Bin& BinContainer::getLastBin() {
    // Initializes new bin if none present
    if (bins.size() == 0) addNewEmptyBin();
    return bins.back();
}

void BinContainer::addNewEmptyBin() {
    Bin newBin = Bin(maxBinCapacity);
    bins.push_back(newBin);
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
    bins.clear();
}
