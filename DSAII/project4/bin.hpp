/***************************************************************
  Student Name: Sarah Wallis
  File Name: bin.hpp
  Assignment number: Project 4

  Class for managing bins
***************************************************************/
#include <vector>

class Bin {
    private:
        double maxBinCapacity;
        double fillAmount; // How full the bin currently is
        std::vector<double> items; // The items currently in the bin
    public:
        Bin(double maxBinCapacity);
        double getCapacity(); // Returns maxBinCapacity
        void setFillAmount(double size);
        double getFillAmount();
        std::vector<double>& getItems(); // Returns a reference to the items vector
        bool tryAddItem(double item); // Returns true or false depending on if the item was successfully added
};