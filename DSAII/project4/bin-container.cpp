#include "./bin-container.hpp"
#include <string>
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
    if (bins.size() == index) addNewEmptyBin();
    return bins.at(index); // Breaks if index is 2 or more greater than bins.size() ; This is intentional behavior
}

Bin& BinContainer::getLastBin() {
    if (bins.size() == 0) addNewEmptyBin();
    return bins.back();
}

void BinContainer::addNewEmptyBin() {
    Bin newBin = Bin(maxBinCapacity);
    bins.push_back(newBin);
}

void BinContainer::print() {
    for (size_t i = 0; i < bins.size(); ++i) {
        std::string result = "";
        result += ("  b" + std::to_string(i+1) + ": ");
        for (auto item : bins.at(i).getItems()) {
            result += (std::to_string(item) + " ");
        }
        std::cout << result << std::endl;
    }
}

void BinContainer::clear() {
    bins.clear();
}
