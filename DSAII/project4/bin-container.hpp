#include "./bin.hpp"
#include <string>
#include <vector>

class BinContainer {
    private:
        std::vector<Bin> bins;
        int binCount;
        int maxBinCapacity;
    public:
        BinContainer();
        BinContainer(int maxBinCapacity);
        int getBinCount();
        Bin getBinAt(int index);
        Bin getLastBin();
        void addNewEmptyBin();
        void print();
        void clear();
};