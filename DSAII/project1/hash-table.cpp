#include "./hash-table.hpp"
using namespace std;

// Pushes a pair made from the given userID and password to the proper bucket's linked list
void HashTable::insert(string userID, string password) {
    int bucketNum = hashFunction(userID);
    table[bucketNum].push_back(make_pair(userID, password));
}

// Iterates over the linked list for the relevant bucket and returns the password if found
string HashTable::search(string userID) {
    int bucketNum = hashFunction(userID);

    if (!table[bucketNum].empty()) {
        for (auto const& node: table[bucketNum]) {
            if (node.first == userID) return node.second;
        }
    }

    return "NOT_FOUND";
}

// Calculates bucket numbers by summing the total ASCII value of a userID's characters and modding it by the table size
int HashTable::hashFunction(string userID) {
    int bucketNum = 0;

    for (auto& character: userID) {
        bucketNum += character;
    }

    bucketNum = bucketNum % tableSize;

    return bucketNum;
}