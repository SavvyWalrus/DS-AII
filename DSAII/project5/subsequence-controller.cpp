/***************************************************************
  Student Name: Sarah Wallis
  File Name: subsequence-controller.cpp
  Assignment number: Project 5

  Class for managing LCS and similarity calculations
***************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "./subsequence-controller.hpp"
#include "./lcs-manager.hpp"
#include "similarity-calculator.hpp"

SubsequenceController::SubsequenceController(std::string twoStringsFilename, std::string multiStringsFilename) {
    this->twoStringsFilename = twoStringsFilename;
    this->multiStringsFilename = multiStringsFilename;
}

void SubsequenceController::runTwoStringsCalculation() {
    // Reads strings from given file name
    std::ifstream buffer(twoStringsFilename);
    std::string twoStrings[2];

    std::getline(buffer, twoStrings[0]);
    std::getline(buffer, twoStrings[1]);

    buffer.close();

    LCSManager lcs(twoStrings[0], twoStrings[1]);

    // Outputs original strings along with their LCS
    std::cout << "Part 1:\nString 1:\n" << twoStrings[0] << "\n\nString 2:\n" << twoStrings[1] << "\n\nLCS:\n" << lcs.calculateLCS() << std::endl;
}

void SubsequenceController::runMultiStringsCalculation() {
    // Reads strings from given file name
    std::ifstream buffer(multiStringsFilename);

    int numStrings;
    buffer >> numStrings;
    std::vector<std::string> multiStrings;

    std::string temp;
    std::getline(buffer, temp);
    for (int i = 0; i < numStrings; ++i) {
        std::getline(buffer, temp);
        multiStrings.push_back(temp);
    }

    buffer.close();
    
    SimilarityCalculator simCalculator(multiStrings);
    simCalculator.runSimilarityCalculations();
    
    std::cout << "Part 2:" << std::endl;
    simCalculator.printSimilarityTable();
}
