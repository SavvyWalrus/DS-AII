#include "./hash-table.hpp"
#include <iostream>
using namespace std;

void HashTable::insert(string userID, string password) {
    int bucketNum = hashFunction(userID);
    table[bucketNum].push_back(make_pair(userID, password));
}

string HashTable::search(string userID) {
    int bucketNum = hashFunction(userID);

    if (!table[bucketNum].empty()) {
        for (auto const& node: table[bucketNum]) {
            if (node.first == userID) return node.second;
        }
    }

    return "NOT_FOUND";
}

int HashTable::hashFunction(string userID) {
    int bucketNum = 0;

    for (auto& character: userID) {
        bucketNum += character;
    }

    bucketNum = bucketNum % tableSize;

    return bucketNum;
}