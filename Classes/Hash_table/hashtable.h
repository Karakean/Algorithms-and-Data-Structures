#pragma once
#include "HashNode.h"
class HashTable {
        HashNode* arr[SIZE];
public:
        HashTable();
        unsigned int hash(std::string key);
        void insert(std::string key, int value);
        void search(std::string key);
        void delete_nodes(HashNode* node);
        ~HashTable();
};