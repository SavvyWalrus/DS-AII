#include "./packing-controller.hpp"
#include <string>
#include <vector>
#include <iostream>

PackingController::PackingController(std::vector<double> items, double maxBinCapacity) {
    this->items = items;
    this->maxBinCapacity = maxBinCapacity;
    binContainers = std::vector<BinContainer>(NUMBER_OF_TYPES);
}

void PackingController::swap(int p, int q, std::vector<double>& s) {
    int temp = s[p];
    s[p] = s[q];
    s[q] = temp;
}

void PackingController::incrementPermutation(std::vector<double>& s) {
    int m, k, p , q;

    m = items.size()-2;
    while(s[m]>s[m+1]) {
        m = m - 1;
    }

    k = items.size()-1;
    while(s[m] > s[k]) {
        k = k - 1;
    }

    swap(m, k, s);
    
    p = m + 1;
    q = items.size() - 1;
    while( p < q) {
        swap(p, q, s);
        ++p;
        --q;
    }

    // printS(s);
}

int PackingController::computeFactorial(int num) {
    if (num <= 1) {
        return 1;
    } else {
        return num * computeFactorial(num - 1);
    }
}

void PackingController::computeOptimalFit() {
    std::vector<double> itemPerm = items;
    int numPermutations = computeFactorial(itemPerm.size());

    for (int i = 0; i < numPermutations; ++i) {
        BinContainer container = BinContainer(maxBinCapacity);

        for (auto item : itemPerm) {
            if (container.getLastBin().tryAddItem(item)) {
                continue;
            } else {
                container.addNewEmptyBin();
                container.getLastBin().tryAddItem(item);
            }
        }

        if (container.getBinCount() < binContainers.at(OPTIMAL_FIT).getBinCount()) {
            binContainers.at(OPTIMAL_FIT) = container;
        }

        incrementPermutation(itemPerm);

        std::cout << "TEST: " << binContainers.at(OPTIMAL_FIT).getBinAt(0).getItems().size() << std::endl;
    }
}

void PackingController::computeOnlineFirstFit() {

}

void PackingController::computeOnlineNextFit() {

}

void PackingController::computeOnlineBestFit() {

}

void PackingController::computeOfflineFirstFit() {

}

void PackingController::computeOfflineBestFit() {

}

void PackingController::runPackingSimulations() {
    computeOptimalFit();
}

void PackingController::print() {
    std::cout << "Optimal:" << binContainers.at(OPTIMAL_FIT).getBinCount() << std::endl;
    binContainers.at(OPTIMAL_FIT).print();
}
