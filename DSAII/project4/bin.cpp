/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin.cpp
  Assignment number: Project 4

  Class for managing bins
***************************************************************/
#include "./bin.hpp"
#include <vector>

Bin::Bin() {
    fillAmount = 0;
    itemCount = 0;
}

double Bin::getCapacity() {
    return MAX_BIN_CAPACITY;
}

void Bin::setFillAmount(double size) {
    this->fillAmount = size;
}

double Bin::getFillAmount() {
    return this->fillAmount;
}

std::vector<double> Bin::getItems() {
    std::vector<double> temp;
    for (int i = 0; i < itemCount; ++i) {
        temp.push_back(items[i]);
    }

    return temp;
}

bool Bin::tryAddItem(double item) {
    if (fillAmount + item <= MAX_BIN_CAPACITY) {
        fillAmount += item;
        items[itemCount] = item;
        ++itemCount;
        return true;
    } else {
        return false;
    }
}

void Bin::clear() {
    fillAmount = 0;
    itemCount = 0;
}