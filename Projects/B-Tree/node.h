#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define MAX_NUMBER_LENGHT 10
class Tree;
class Node {
        bool isLeaf;
        int t;
        int cntKey;
        int* keys;
        Node** sons;
        friend Tree;
public:
        Node(bool _isLeaf, int _t);
        Node* search(int key);
        void print();
        void insert(int key);
        void split(Node* node, int index);
        void save();
        ~Node();
};