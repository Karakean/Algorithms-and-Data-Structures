#include "Node.h"
Node::Node(bool _isLeaf, int _t) {
    this->t = _t;
        this->isLeaf = _isLeaf;
        this->cntKey = 0;
        this->keys = new int[2 * t - 1];
        this->sons = new Node* [2 * t];
}
Node* Node::search(int key) {
        int i = 0;
        while (i < cntKey && key > keys[i])
                i++;
        if (key == keys[i])
                return this;
        if (isLeaf)
                return nullptr;
        return sons[i]->search(key);
}
void Node::print() {
        int i = 0;
        while (i < cntKey) {
                if (!isLeaf)
                        sons[i]->print();
                printf(" %d", keys[i]);
                i++;
        }
        if (!isLeaf)
                sons[i]->print();
}
void Node::insert(int key) {
    int i = cntKey - 1;
    if(!isLeaf)
    {
        while (i >= 0 && keys[i] > key)
            i--;
        if (sons[i + 1]->cntKey == 2 * t - 1)
        {
            split(sons[i + 1], i + 1);
            if (keys[i + 1] < key)
                i++;
        }
        sons[i + 1]->insert(key);
    }
    else
    {
        while (i >= 0 && keys[i] > key)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        cntKey++;
    }
}
void Node::split(Node* node, int index) {
    Node* new_node = new Node(node->isLeaf, node->t);
    new_node->cntKey = t - 1;
    for (int i = 0; i < t - 1; i++)
        new_node->keys[i] = node->keys[i + t];
    if (!node->isLeaf)
    {
        for (int i = 0; i < t; i++)
            new_node->sons[i] = node->sons[i + t];
    }
    node->cntKey = t - 1;
    for (int i = cntKey; i > index; i--)
        sons[i + 1] = sons[i];
    sons[index + 1] = new_node;
    for (int i = cntKey - 1; i >= index; i--)
        keys[i + 1] = keys[i];
    keys[index] = node->keys[t - 1];
        cntKey++;
}
void Node::save() {
    int i = 0;
    printf(" (");
    while (i < cntKey) {
        if (!isLeaf)
            sons[i]->save();
        printf(" %d", keys[i]);
        i++;
    }
    if (!isLeaf)
        sons[i]->save();
    printf(" )");
}
Node::~Node() {
    delete[] this->sons;
    delete[] this->keys;
}