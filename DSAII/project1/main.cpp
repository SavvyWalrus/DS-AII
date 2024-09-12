#include "./password-manager.hpp"

int main() {
    PasswordManager manager;
    manager.testLegalPasswords();
    manager.testIllegalPasswords();
    
    return 0;
}