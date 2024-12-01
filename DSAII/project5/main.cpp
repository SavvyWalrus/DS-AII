/***************************************************************
  Student Name: Sarah Wallis
  File Name: main.cpp
  Assignment number: Project 5

  Main function for running program
***************************************************************/
#include <iostream>
#include "./subsequence-controller.hpp"
#define TWO_STRINGS_FILENAME "./twoStrings.txt"
#define MULTI_STRINGS_FILENAME "./multiStrings.txt"

int main() {
    SubsequenceController controller(TWO_STRINGS_FILENAME, MULTI_STRINGS_FILENAME);
    controller.runTwoStringsCalculation();
    std::cout << std::endl;
    controller.runMultiStringsCalculation();

    return 0;
}