#include <vector>
#include "./bin-container.hpp"

class PackingController {
    private:
        struct {
            const int OPTIMAL_FIT = 0;
            const int ONLINE_FIRST_FIT = 1;
            const int ONLINE_NEXT_FIT = 2;
            const int ONLINE_BEST_FIT = 3;
            const int OFFLINE_FIRST_FIT = 4;
            const int OFFLINE_BEST_FIT = 5;
            const int NUMBER_OF_TYPES = 6;
        };
        std::vector<BinContainer> binContainers;
        std::vector<double> items;
        double maxBinCapacity;
        void insertionSort(std::vector<double>& s);
        void swap(int p, int q, std::vector<int>& s);
        void incrementPermutation(std::vector<int>& s);
        void printS(std::vector<double>& s);
        size_t computeFactorial(size_t num);
        void computeOptimalFit();
        void computeFirstFit(int algoType, std::vector<double> itemsList);
        void computeNextFit(int algoType, std::vector<double> itemsList);
        void computeBestFit(int algoType, std::vector<double> itemsList);
    public:
        PackingController(std::vector<double> items, double maxBinCapacity);
        void runPackingSimulations();
        void print();
};