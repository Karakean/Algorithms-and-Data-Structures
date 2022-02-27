#include "HashNode.h"
HashNode::HashNode() {
        this->value = 0;
        this->key = "";
        this->next = nullptr;
}
HashNode::HashNode(int value, std::string key, HashNode* next) {
        this->value = value;
        this->key = key;
        this->next = next;
}