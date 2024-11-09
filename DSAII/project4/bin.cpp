/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin.cpp
  Assignment number: Project 4

  Class for managing bins
***************************************************************/
#include "./bin.hpp"

Bin::Bin(double maxBinCapacity) {
    this->maxBinCapacity = maxBinCapacity;
    fillAmount = 0;
}

double Bin::getCapacity() {
    return this->maxBinCapacity;
}

void Bin::setFillAmount(double size) {
    this->fillAmount = size;
}

double Bin::getFillAmount() {
    return this->fillAmount;
}

std::vector<double>& Bin::getItems() {
    return items;
}

bool Bin::tryAddItem(double item) {
    if (fillAmount + item <= maxBinCapacity) {
        setFillAmount(fillAmount + item);
        items.push_back(item);
        return true;
    } else {
        return false;
    }
}