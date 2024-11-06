#include "./bin-container.hpp"
#include <cmath>
#include <string>
#include <iostream>

BinContainer::BinContainer() {
    binCount = INFINITY;
    maxBinCapacity = -1;
}

BinContainer::BinContainer(int maxBinCapacity) {
    binCount = 0;
    this->maxBinCapacity = maxBinCapacity;
}

int BinContainer::getBinCount() {
    return binCount;
}

Bin BinContainer::getBinAt(int index) {
    return bins.at(index);
}

Bin BinContainer::getLastBin() {
    if (bins.size() == 0) addNewEmptyBin();
    return bins.at(bins.size() - 1);
}

void BinContainer::addNewEmptyBin() {
    Bin newBin = Bin(maxBinCapacity);
    bins.push_back(newBin);
    ++binCount;
}

void BinContainer::print() {
    for (size_t i = 0; i < bins.size(); ++i) {
        std::string result = "";
        result += ("  b" + std::to_string(i+1) + ": ");
        for (auto item : bins.at(i).getItems()) {
            result += (std::to_string(item) + " ");
        }
        result += "\n";
        std::cout << result << std::endl;
    }
}

void BinContainer::clear() {
    bins.clear();
    binCount = 0;
}
