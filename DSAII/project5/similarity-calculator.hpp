/***************************************************************
  Student Name: Sarah Wallis
  File Name: similarity-calculator.hpp
  Assignment number: Project 5

  Class for evaluating similarity for a given list of strings
***************************************************************/
#ifndef SIMILARITY_CALCULATOR_HPP
#define SIMILARITY_CALCULATOR_HPP
#include "./two-d-array.hpp"
#include <vector>

class SimilarityCalculator {
    private:
        TwoDArray<char> similarityTable; // Stores respective chars for similarity rating
        std::vector<std::string> stringList; // Stores all the strings for comparison
    public:
        SimilarityCalculator(std::vector<std::string>& stringList); // Parameterized constructor
        void runSimilarityCalculations(); // Runs all comparison calculations for similarity ratings
        void printSimilarityTable(); // Outputs a formatted version of the table to the console
};

#endif