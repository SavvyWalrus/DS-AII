/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin-container.hpp
  Assignment number: Project 4

  Class for managing bin containers
***************************************************************/
#include "./bin.hpp"
#include "./constants.hpp"

class BinContainer {
    private:
        Bin bins[MAX_NUM_BINS];
        int binCount;
    public:
        BinContainer();
        int getBinCount(); // Returns the current size of the bins vector
        Bin& getBinAt(int index); // Returns a reference to the bin at index ; Adds a new bin and returns that if the index is out of range
        Bin& getLastBin(); // Returns a reference to the last bin ; Adds a new empty bin if size is zero and returns it
        void addNewEmptyBin();
        void addNewItemByNextFit(double item);
        void addNewItemByFirstFit(double item);
        void print(); // Prints the contents of each bin
        void clear(); // Empties the bins
};