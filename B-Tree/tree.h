#pragma once
#include "Node.h"
class Tree {
        int t;
        Node* root;
        static int calculate(int* arr, int n);
public:
        Tree();
        void setOrder(int _t);
        void setRoot(Node* r);
        void printTree();
        void treeInsert(int key);
        void treeSave();
        void deleteSons(Node* node);
        Node* treeSearch(int key);
        Node* load();
        ~Tree();
};