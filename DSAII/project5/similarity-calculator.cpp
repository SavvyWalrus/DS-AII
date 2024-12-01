/***************************************************************
  Student Name: Sarah Wallis
  File Name: similarity-calculator.cpp
  Assignment number: Project 5

  Class for evaluating similarity for a given list of strings
***************************************************************/
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <ios>
#include "./similarity-calculator.hpp"
#include "lcs-manager.hpp"
#include "two-d-array.hpp"

SimilarityCalculator::SimilarityCalculator(std::vector<std::string>& stringList) {
    this->stringList = stringList;
    similarityTable = TwoDArray<char>(stringList.size(), stringList.size(), '-'); // Sets default rating to '-' placeholder
}

void SimilarityCalculator::runSimilarityCalculations() {
    LCSManager lcs(stringList[0], stringList[0]);

    for (size_t i = 0; i < stringList.size(); ++i) {
        for (size_t j = i+1; j < stringList.size(); ++j) {
            lcs.setStrings(stringList[i], stringList[j]);

            // Values for similarity evaluation
            int lcsLength = lcs.calculateLCSLength();
            double lengthComparisonRatio = static_cast<double>(std::min(stringList[i].size(), stringList[j].size())) / std::max(stringList[i].size(), stringList[j].size());
            double lcsComparisonRatio = static_cast<double>(lcsLength) / std::min(stringList[i].size(), stringList[j].size());

            if (lengthComparisonRatio > 0.9 && lcsComparisonRatio >= 0.9) {
                similarityTable.setValue(i, j, 'H'); // High
            } else if (lengthComparisonRatio > 0.8 && lcsComparisonRatio >= 0.8) {
                similarityTable.setValue(i, j, 'M'); // Medium
            } else if (lengthComparisonRatio > 0.6 && lcsComparisonRatio >= 0.5) {
                similarityTable.setValue(i, j, 'L'); // Low
            } else {
                similarityTable.setValue(i, j, 'D'); // Dissimilar
            }
        }
    }
}

void SimilarityCalculator::printSimilarityTable() {
    std::cout << "   ";
    for (size_t i = 0; i < stringList.size(); ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::fixed << i+1 << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < similarityTable.getRowCount(); ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::fixed << i+1 << " ";
        for (size_t j = 0; j < similarityTable.getColCount(); ++j) {
            std::cout << " " << similarityTable.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
