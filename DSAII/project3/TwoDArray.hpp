#ifndef TWO_D_ARRAY
#define TWO_D_ARRAY
#include <cstddef>

template <typename T>
class TwoDArray {
    private:
        T** array;
        size_t rows;
        size_t cols;
    public:
        TwoDArray() = delete; // Prevents use of default constructor
        TwoDArray(size_t rows, size_t cols, T defaultValue);
        TwoDArray(const TwoDArray& arrayToCopy);
        TwoDArray& operator=(const TwoDArray& arrayToCopy);
        ~TwoDArray();
        T getValue(size_t row, size_t col) const;
        void setValue(size_t row, size_t col, T value);
        size_t getRowCount() const;
        size_t getColCount() const;
};

#endif