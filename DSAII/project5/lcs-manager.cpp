/***************************************************************
  Student Name: Sarah Wallis
  File Name: lcs-manager.cpp
  Assignment number: Project 5

  Class for calculating the LCS of any two given strings
***************************************************************/
#include <stack>
#include <string>
#include "./lcs-manager.hpp"
#include "./two-d-array.hpp"

LCSManager::LCSManager(std::string str1, std::string str2) {
    this->str1 = str1;
    this->str2 = str2;
    this->lcs = "";
}

void LCSManager::setStrings(std::string str1, std::string str2) {
    this->str1 = str1;
    this->str2 = str2;
    this->lcs = ""; // Clears LCS for new calculation
}

std::string LCSManager::getStr1() {
    return str1;
}

std::string LCSManager::getStr2() {
    return str2;
}

std::string LCSManager::calculateLCS() {
    if (lcs != "") return lcs; // Avoids recalculating until lcs has been reset

    // Algorithm for building LCS table
    // Adapted from psuedocode in class
    int m = str1.length();
    int n = str2.length();
    TwoDArray<int> c(m+1, n+1, 0);

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int newValue;

            if (str1[i-1] == str2[j-1]) {
                newValue = c.getValue(i-1, j-1) + 1;
            } else {
                if (c.getValue(i-1, j) >= c.getValue(i, j-1)) {
                    newValue = c.getValue(i-1, j);
                } else {
                    newValue = c.getValue(i, j-1);
                }
            }

            c.setValue(i, j, newValue);
        }
    }

    // Iterative lcs reconstruction using a stack
    std::stack<char> strRev;
    int currRow = m;
    int currCol = n;
    
    while (c.getValue(currRow, currCol) > 0) {
        if (str1[currRow-1] == str2[currCol-1]) {
            strRev.push(str1[currRow-1]);
            --currRow;
            --currCol;
        } else {
            if (c.getValue(currRow-1, currCol) >= c.getValue(currRow, currCol-1)) {
                --currRow;
            } else {
                --currCol;
            }
        }
    }

    while (!strRev.empty()) {
        lcs += strRev.top();
        strRev.pop();
    }

    return lcs;
}

int LCSManager::calculateLCSLength() {
    int m = str1.length();
    int n = str2.length();
    TwoDArray<int> c(2, n+1, 0); // Only two rows at a time

    // Calculates LCS length for given strings
    // Adapted from psuedocode in class
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int newValue;

            if (str1[i-1] == str2[j-1]) {
                newValue = c.getValue(0, j-1) + 1;
            } else {
                if (c.getValue(0, j) >= c.getValue(1, j-1)) {
                    newValue = c.getValue(0, j);
                } else {
                    newValue = c.getValue(1, j-1);
                }
            }

            c.setValue(1, j, newValue);
        }

        // Overwrites current row with previous after every row has been evaluated
        for (int j = 0; j <= n; ++j) {
            int newValue = c.getValue(1, j);
            c.setValue(0, j, newValue);
        }
    }

    return c.getValue(1, n); // Returns the very last calculated value which should always be the length of the LCS
}
