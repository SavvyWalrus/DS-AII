#include <vector>

class Bin {
    private:
        double maxBinCapacity;
        double fillAmount;
        std::vector<double> items;
    public:
        Bin(double maxBinCapacity);
        double getCapacity();
        void setFillAmount(double size);
        double getFillAmount();
        std::vector<double> getItems();
        bool tryAddItem(double item);
};