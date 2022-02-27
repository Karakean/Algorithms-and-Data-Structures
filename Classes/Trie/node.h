#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#define MAX_WORD_LENGTH 16
#define ALPHABET_LENGTH 26
class Tree;
class Node {
        Node* children[ALPHABET_LENGTH];
        std::string translation;
        bool isWord;
        void traverse();
public:
        Node();
        void addWord(std::string word, std::string _translation);
        Node* search(std::string word);
        void printWords(std::string prefix);
        std::string getTranslation() const;
        void deleteChildren();
        ~Node();
};