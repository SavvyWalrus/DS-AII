#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <list>
#include <string>
using namespace std;

class HashTable {
    public:
        void insert(string userID, string password);
        string search(string userID);
    private:
        int tableSize = 100;
        list<pair<string, string>> table[100];
        int hashFunction(string userID);
};

#endif