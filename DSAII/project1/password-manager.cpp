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
    encryptPasswords();
}

void PasswordManager::generateRawData() {
    ofstream rawdata;
    ifstream names;
    string tempRawLine;
    string tempPassword = "";

    rawdata.open("rawdata.txt");
    names.open("names.txt");

    while (getline(names, tempRawLine)) {
        istringstream buffer(tempRawLine);
        string name;
        tempPassword = "";

        buffer >> name;

        for (int i = 0; i < passwordLength; ++i) {
            tempPassword += char(rand()%('z' - 'a' + 1) + 'a');
        }

        rawdata << left << setw(15) << name << " " << tempPassword << endl;
    }

    rawdata.close();
    names.close();
}

void PasswordManager::encryptPasswords() {
    ofstream encryptedData;
    ifstream rawdata;
    string tempRawLine;
    string tempUserID;
    string tempRawPassword;
    string encryptedPassword;

    rawdata.open("rawdata.txt");
    encryptedData.open("encrypteddata.txt");

    while (getline(rawdata, tempRawLine)) {
        istringstream buffer(tempRawLine);

        buffer >> tempUserID >> tempRawPassword;

        encryptedPassword = vigenereCypher(tempRawPassword);

        encryptedData << left << setw(15) << tempUserID << " " << encryptedPassword << endl;
    }

    rawdata.close();
    encryptedData.close();
}

string PasswordManager::vigenereCypher(string tempRawPassword) {
    string encryptedPassword = "";

    for (int i = 0; i < passwordLength; ++i) {
        int offset = key[i % key.size()] - 'a'; // Calculates the character offset.
        int charPlusOffset = tempRawPassword[i] + offset; // Adds the calculated offset to the current character in the unencrypted password.

        if (charPlusOffset == 'z' + 1) { // Accounts for the needed space character following 'z' in the alphabet.
            charPlusOffset = ' ';
        } else if (charPlusOffset > 'z' + 1) {
            // Calculates the proper ASCII code for when the result loops back to the start of the alphabet.
            // Subtracts 1 to account for the off by one logic error introduced by using 'a'.
            charPlusOffset = 'a' + (charPlusOffset - ('z' + 1)) - 1;
        }

        // Adds the calculated character to the encrypted password string.
        encryptedPassword += charPlusOffset;
    }

    return encryptedPassword;
}