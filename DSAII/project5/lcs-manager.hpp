/***************************************************************
  Student Name: Sarah Wallis
  File Name: lcs-manager.hpp
  Assignment number: Project 5

  Class for calculating the LCS of any two given strings
***************************************************************/
#ifndef LCS_MANAGER_HPP
#define LCS_MANAGER_HPP
#include <string>

class LCSManager {
    private:
        // Strings for LCS algorithm
        std::string str1;
        std::string str2;

        // Found LCS string
        std::string lcs;
    public:
        // Parameterized constructor
        LCSManager(std::string str1, std::string str2);

        // Setter for both strings ; Resets LCS
        void setStrings(std::string str1, std::string str2);

        // Getters for stored strings
        std::string getStr1();
        std::string getStr2();

        // Calculates and returns the found LCS
        std::string calculateLCS();

        // Only calculates LCS length and returns the value
        int calculateLCSLength();
};

#endif