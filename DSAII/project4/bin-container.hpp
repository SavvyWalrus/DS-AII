#include "./bin.hpp"
#include <cstddef>
#include <vector>

class BinContainer {
    private:
        std::vector<Bin> bins;
        int maxBinCapacity;
    public:
        BinContainer();
        BinContainer(int maxBinCapacity);
        int getBinCount();
        Bin& getBinAt(size_t index);
        Bin& getLastBin();
        void addNewEmptyBin();
        void print();
        void clear();
};