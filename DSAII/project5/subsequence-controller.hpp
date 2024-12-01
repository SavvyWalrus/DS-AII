/***************************************************************
  Student Name: Sarah Wallis
  File Name: subsequence-controller.hpp
  Assignment number: Project 5

  Class for managing LCS and similarity calculations
***************************************************************/
#ifndef SUBSEQUENCE_CONTROLLER_HPP
#define SUBSEQUENCE_CONTROLLER_HPP
#include <string>

class SubsequenceController {
    private:
        std::string twoStringsFilename;
        std::string multiStringsFilename;
    public:
        SubsequenceController(std::string twoStringsFilename, std::string multiStringsFilename);
        void runTwoStringsCalculation(); // Runs LCS for given two strings
        void runMultiStringsCalculation(); // Runs similarity calculations for given list of strings
};

#endif