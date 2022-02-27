#pragma once
#include <iostream>
#include <string>
#define SIZE 1000
class HashNode {
public:
        int value;
        std::string key;
        HashNode* next;
        HashNode();
        HashNode(int value, std::string key, HashNode* next);
};