#include "./password-manager.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

// Default constructor ; Auto writes txt data and builds hash table
PasswordManager::PasswordManager() {
    generateRawData();
    encryptPasswords();
    buildHashTable();
}

// Parses names.txt and writes extracted userIDs and randomized passwords to rawdata.txt
void PasswordManager::generateRawData() {
    ofstream rawdata;
    ifstream names;
    string tempRawLine;
    string tempPassword = "";

    // Opens the input and output text files
    rawdata.open("rawdata.txt");
    names.open("names.txt");

    // Loops until the end of names.txt, inserting each line into tempRawLine
    while (getline(names, tempRawLine)) {
        istringstream buffer(tempRawLine); // Adds the current line to a stream buffer
        string name;
        tempPassword = "";

        buffer >> name; // Extracts the first entry in the current line in the buffer into the name variable

        // Generates a random password of lowercase letters
        for (int i = 0; i < passwordLength; ++i) {
            tempPassword += char(rand()%('z' - 'a' + 1) + 'a'); // Produces a random character from the minimum 'a' to the maximum 'z' and adds it to the password
        }

        // Writes the userID and password into the output file in two columns
        rawdata << left << setw(15) << name << " " << tempPassword << endl;
    }

    // Closes the file streams
    rawdata.close();
    names.close();
}

// Takes the userID password pairs from rawdata.txt, ecrypts the passwords, and writes them to encrypteddata.txt
void PasswordManager::encryptPasswords() {
    ofstream encrypteddata;
    ifstream rawdata;
    string tempRawLine;
    string tempUserID;
    string tempRawPassword;
    string encryptedPassword;

    // Opens the files for each data type
    rawdata.open("rawdata.txt");
    encrypteddata.open("encrypteddata.txt");

    // Loops until the end of rawdata.txt, inserting each line into tempRawLine
    while (getline(rawdata, tempRawLine)) {
        istringstream buffer(tempRawLine); // Adds the current line to a stream buffer

        buffer >> tempUserID >> tempRawPassword; // Extracts the current line's userID and password

        encryptedPassword = vigenereCypher(tempRawPassword); // Encrypts the password

        encrypteddata << left << setw(15) << tempUserID << " " << encryptedPassword << endl; // Writes the userID and encrypted password to encrypteddata.txt
    }

    // Closes the file streams
    rawdata.close();
    encrypteddata.close();
}

// Custom vigenere cypher for encryption based on a given key's character offsets
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

// Builds a hash table from the pairs with encrypted passwords
void PasswordManager::buildHashTable() {
    ifstream myfile;
    string tempLine;
    string userID;
    string password;

    myfile.open("encrypteddata.txt");

    // Loops until the end of encrypteddata.txt, inserting each line into tempLine
    while (getline(myfile, tempLine)) {
        istringstream buffer(tempLine);
        buffer >> userID;
        getline(buffer >> ws, password); // Ignores leading whitespace but grabs whole password ; May break if password starts with any whitespace
        encryptedTable.insert(userID, password);
    }

    myfile.close();
}

// Tests and compares the passwords of the given indeces in rawdata.txt to those contained in the hash table
void PasswordManager::testLegalPasswords() {
    int currentLine = -1; // Starts at -1 to account for off by one logic error
    int testIndeces[5] = {0, 2, 4, 6, 8}; // List of test names indeces
    ifstream rawdata;
    string userID;
    string filePassword;
    string encryptedFilePassword;
    string hashPassword;
    string tempLine;

    // Outputs the table header
    cout << "Legal:\n" << endl;
    cout << left << setw(15) << "Userid" << " Password(file)" << " Password(table/un)" << " Result" << endl;

    // Opens the input file stream
    rawdata.open("rawdata.txt");

    // Iterates through each name index provided by testIndeces
    for (auto& index: testIndeces) {
        // Reads line data and extracts the relevant userID and plaintext password
        do {
            getline(rawdata, tempLine);
            istringstream buffer(tempLine);

            buffer >> userID >> filePassword;
            ++currentLine;
        } while (currentLine != index); // Loops past irrelevant lines

        hashPassword = encryptedTable.search(userID); // Uses the extracted userID for the hash lookup
        encryptedFilePassword = vigenereCypher(filePassword); // Encrypts the extracted plaintext password

        // Outputs the row for the current userID
        cout << left << setw(18) << userID << setw(16) << encryptedFilePassword << setw(15) << hashPassword << " " << (encryptedFilePassword == hashPassword ? "match" : "no match") << endl;
    }

    cout << endl << endl;
}

// Tests and compares modified passwords of the given indeces in rawdata.txt to those contained in the hash table
void PasswordManager::testIllegalPasswords() {
    int currentLine = -1; // Starts at -1 to account for off by one logic error
    int testIndeces[5] = {0, 2, 4, 6, 8}; // List of test names indeces
    ifstream rawdata;
    string userID;
    string filePassword;
    string encryptedFilePassword;
    string hashPassword;
    string tempLine;

    // Outputs the table header
    cout << "Illegal:\n" << endl;
    cout << left << setw(15) << "Userid" << " Password(mod)" << " Password(table/un)" << " Result" << endl;

    // Opens the input file stream
    rawdata.open("rawdata.txt");

    // Iterates through each name index provided by testIndeces
    for (auto& index: testIndeces) {
        // Reads line data and extracts the relevant userID and plaintext password
        do {
            getline(rawdata, tempLine);
            istringstream buffer(tempLine);

            buffer >> userID >> filePassword;
            ++currentLine;
        } while (currentLine != index); // Loops past irrelevant lines

        // Modifies the plaintext password
        filePassword[0] = 'q';

        hashPassword = encryptedTable.search(userID); // Uses the extracted userID for the hash lookup
        encryptedFilePassword = vigenereCypher(filePassword); // Encrypts the extracted plaintext password

        // Outputs the row for the current userID
        cout << left << setw(18) << userID << setw(16) << encryptedFilePassword << setw(14) << hashPassword << " " << (encryptedFilePassword == hashPassword ? "match" : "no match") << endl;
    }
}