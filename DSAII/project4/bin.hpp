/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin.hpp
  Assignment number: Project 4

  Class for managing bins
***************************************************************/
#include <vector>
#include "./constants.hpp"

class Bin {
    private:
        double fillAmount; // How full the bin currently is
        double items[MAX_NUM_BINS]; // The items currently in the bin
        int itemCount;
    public:
        Bin();
        double getCapacity(); // Returns maxBinCapacity
        void setFillAmount(double size);
        double getFillAmount();
        std::vector<double> getItems(); // Returns a vector copy of the items array
        bool tryAddItem(double item); // Returns true or false depending on if the item was successfully added
        void clear();
};