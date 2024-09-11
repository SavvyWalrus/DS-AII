#ifndef PASSWORD_MANAGER
#define PASSWORD_MANAGER

#include <string>
using namespace std;

class PasswordManager {
    public:
        PasswordManager();
        void generateRawData();
        void encryptPasswords();
        string testLegalPasswords();
        string testIllegalPasswords();
    private:
        string key = "jones";
        int passwordLength = 9;
};

#endif