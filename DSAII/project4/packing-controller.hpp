#include <vector>
#include "./bin-container.hpp"

class PackingController {
    private:
        struct {
            const int OPTIMAL_FIT = 0;
            const int ONLINE_FIRST = 1;
            const int ONLINE_NEXT_FIT = 2;
            const int ONLINE_BEST_FIT = 3;
            const int OFFLINE_FIRST_FIT = 4;
            const int OFFLINE_BEST_FIT = 5;
            const int NUMBER_OF_TYPES = 6;
        };
        std::vector<BinContainer> binContainers;
        std::vector<double> items;
        double maxBinCapacity;
        void swap(int p, int q, std::vector<double>& s);
        void incrementPermutation(std::vector<double>& s);
        int computeFactorial(int num);
        void computeOptimalFit();
        void computeOnlineFirstFit();
        void computeOnlineNextFit();
        void computeOnlineBestFit();
        void computeOfflineFirstFit();
        void computeOfflineBestFit();
    public:
        PackingController(std::vector<double> items, double maxBinCapacity);
        void runPackingSimulations();
        void print();
};