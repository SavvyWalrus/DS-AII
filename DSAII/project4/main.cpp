/***************************************************************
  Student Name: Sarah Wallis
  File Name: main.cpp
  Assignment number: Project 4

  Main function for running program
***************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include "./packing-controller.hpp"

static const int MAX_BIN_CAPACITY = 1;

int main() {
    std::ifstream buffer("./items.txt");
    std::vector<double> myItems;

    double item;
    int numItems;
    buffer >> numItems;
    for (int i = 0; i < numItems; ++i) {
        buffer >> item;
        myItems.push_back(item);
    }

    PackingController controller = PackingController(myItems, MAX_BIN_CAPACITY);
    controller.runPackingSimulations();
    controller.print();

    return 0;
}