#include "./TwoDArray.hpp"
#include <cstddef>
#include <iostream>

// Constructor
template <typename T>
TwoDArray<T>::TwoDArray(size_t rows, size_t cols, T defaultValue) {
    this->rows = rows;
    this->cols = cols;
    array = new T*[rows];

    for (size_t i = 0; i < rows; ++i) {
        array[i] = new T[cols];
        for (size_t j = 0; j < cols; ++j) {
            array[i][j] = defaultValue;
        }
    }
}

// Destructor
template <typename T>
TwoDArray<T>::~TwoDArray() {
    for (size_t i = 0; i < rows; ++i) {
        delete[] array[i];
    }

    delete[] array;
    array = nullptr;
}

// Copy constructor
template <typename T>
TwoDArray<T>::TwoDArray(const TwoDArray& arrayToCopy) {
    rows = arrayToCopy.rows;
    cols = arrayToCopy.cols;
    array = new T*[rows];

    for (size_t i = 0; i < rows; ++i) {
        array[i] = new T[cols];
        for (size_t j = 0; j < cols; ++j) {
            array[i][j] = arrayToCopy.array[i][j];
        }
    }
}

// Assignment operator
template <typename T>
TwoDArray<T>& TwoDArray<T>::operator=(const TwoDArray& arrayToCopy) {
    if (this == &arrayToCopy) return *this;

    for (size_t i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;

    rows = arrayToCopy.rows;
    cols = arrayToCopy.cols;
    array = new T*[rows];

    for (size_t i = 0; i < rows; ++i) {
        array[i] = new T[cols];
        for (size_t j = 0; j < cols; ++j) {
            array[i][j] = arrayToCopy.array[i][j];
        }
    }

    return *this;
}

template <typename T>
T TwoDArray<T>::getValue(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return T();
    }

    return array[row][col];
}

template <typename T>
void TwoDArray<T>::setValue(size_t row, size_t col, T value) {
    if (row >= rows || col >= cols) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return;
    }
    
    array[row][col] = value;
}

template <typename T>
size_t TwoDArray<T>::getRowCount() const {
    return rows;
}

template <typename T>
size_t TwoDArray<T>::getColCount() const {
    return cols;
}
