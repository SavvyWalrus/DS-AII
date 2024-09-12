#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#define NUM_BUCKETS 100

#include <string>
#include "./linked-list.hpp"
using namespace std;

class HashTable {
    public:
        void insert(string userID, string password);
        string search(string userID);
    private:
        int tableSize = NUM_BUCKETS; // Number of buckets
        LinkedList table[NUM_BUCKETS]; // Assigns an array of linked lists of size NUM_BUCKETS to the table
        int hashFunction(string userID);
};

#endif