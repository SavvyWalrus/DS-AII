#ifndef PASSWORD_MANAGER
#define PASSWORD_MANAGER

#include "hash-table.hpp"
#include <string>
using namespace std;

class PasswordManager {
    public:
        PasswordManager();
        void generateRawData();
        void encryptPasswords();
        void buildHashTables();
        void testLegalPasswords();
        void testIllegalPasswords();
    private:
        string key = "jones";
        int passwordLength = 9;
        string vigenereCypher(string tempRawPassword);
        HashTable rawHash;
        HashTable encryptedHash;
};

#endif