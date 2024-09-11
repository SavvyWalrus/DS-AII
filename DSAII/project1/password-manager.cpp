#include "./password-manager.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

PasswordManager::PasswordManager() {
    generateRawData();
}

void PasswordManager::generateRawData() {
    ofstream rawdata;
    ifstream names;
    string tempRawLine;
    string tempPassword = "";
    char aAscii = 'a';
    char zAscii = 'z';

    rawdata.open("rawdata.txt");
    names.open("names.txt");

    while (getline(names, tempRawLine)) {
        istringstream buffer(tempRawLine);
        string name;
        tempPassword = "";

        buffer >> name;

        for (int i = 0; i < passwordLength; ++i) {
            tempPassword += char(rand()%(zAscii - aAscii + 1) + aAscii);
        }

        rawdata << left << setw(15) << name << " " << tempPassword << endl;
    }

    rawdata.close();
    names.close();
}
