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
    buildHashTables();
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
    ofstream encrypteddata;
    ifstream rawdata;
    string tempRawLine;
    string tempUserID;
    string tempRawPassword;
    string encryptedPassword;

    rawdata.open("rawdata.txt");
    encrypteddata.open("encrypteddata.txt");

    while (getline(rawdata, tempRawLine)) {
        istringstream buffer(tempRawLine);

        buffer >> tempUserID >> tempRawPassword;

        encryptedPassword = vigenereCypher(tempRawPassword);

        encrypteddata << left << setw(15) << tempUserID << " " << encryptedPassword << endl;
    }

    rawdata.close();
    encrypteddata.close();
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

void PasswordManager::buildHashTables() {
    ifstream myfile;
    string tempLine;
    string userID;
    string password;

    myfile.open("encrypteddata.txt");

    while (getline(myfile, tempLine)) {
        istringstream buffer(tempLine);
        buffer >> userID >> password;
        encryptedHash.insert(userID, password);
    }

    myfile.close();
}

void PasswordManager::testLegalPasswords() {
    int currentLine = -1;
    int testIndeces[5] = {0, 2, 4, 6, 8};
    ifstream rawdata;
    string userID;
    string filePassword;
    string encryptedFilePassword;
    string hashPassword;
    string tempLine;

    cout << "Legal:\n" << endl;
    cout << left << setw(15) << "Userid" << " Password(file)" << " Password(table/un)" << " Result" << endl;

    rawdata.open("rawdata.txt");

    for (auto& index: testIndeces) {
        do {
            getline(rawdata, tempLine);
            istringstream buffer(tempLine);

            buffer >> userID >> filePassword;
            ++currentLine;
        } while (currentLine != index);

        hashPassword = encryptedHash.search(userID);
        encryptedFilePassword = vigenereCypher(filePassword);

        cout << left << setw(18) << userID << setw(16) << encryptedFilePassword << setw(15) << hashPassword << " " << (encryptedFilePassword == hashPassword ? "match" : "no match") << endl;
    }
}