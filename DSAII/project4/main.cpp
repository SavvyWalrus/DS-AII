#include <iostream>
#include <fstream>
#include <vector>
#include "./packing-controller.hpp"

static const int MAX_BIN_CAPACITY = 1;

int main() {
    std::ifstream buffer("./items.txt");
    std::vector<double> myItems;

    double item;
    buffer >> item;
    while (buffer >> item) {
        myItems.push_back(item);
    }

    PackingController controller = PackingController(myItems, MAX_BIN_CAPACITY);
    controller.runPackingSimulations();
    controller.print();

    return 0;
}