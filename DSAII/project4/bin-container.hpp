/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin-container.hpp
  Assignment number: Project 4

  Class for managing bin containers
***************************************************************/
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
        int getBinCount(); // Returns the current size of the bins vector
        Bin& getBinAt(size_t index); // Returns a reference to the bin at index ; Adds a new bin and returns that if the index is out of range
        Bin& getLastBin(); // Returns a reference to the last bin ; Adds a new empty bin if size is zero and returns it
        void addNewEmptyBin();
        void print(); // Prints the contents of each bin
        void clear(); // Empties the bins
};