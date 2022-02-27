#include "HashTable.h"
HashTable::HashTable() {
        for (int i = 0; i < SIZE; i++)
                this->arr[i] = nullptr;
}
unsigned int HashTable::hash(std::string key) {
        unsigned int tmp = 0;
        for (std::size_t i = 0; i < key.length(); i++) {
                tmp += ((int)key[i] * (i+7));
        }
        return tmp % SIZE;
}
void HashTable::insert(std::string key, int value) {

        int i = hash(key);
        if (this->arr[i] != nullptr)
        {
                HashNode* curr = arr[i];
                while (1)
                {
                        if (curr->key == key) {
                                curr->value += value;
                                break;
                        }
                        else
                        {
                                if (curr->next == nullptr) {
                                        arr[i] = new HashNode(value, key, arr[i]);
                                        break;
                                }
                                else
                                        curr = curr->next;
                        }
                }
        }
        else
                arr[i] = new HashNode(value, key, nullptr);
}
void HashTable::search(std::string key) {

        int i = hash(key);
        if (this->arr[i] != nullptr)
        {
                HashNode* curr = arr[i];
                while (1)
                {
                        if (curr->key != key) {
                                if (curr->next == nullptr)
                                {
                                        printf("0\n");
                                        break;
                                }
                                else
                                        curr = curr->next;
                        }
                        else {
                                printf("%d\n", curr->value);
                                break;
                        }
                }
        }
        else
                printf("0\n");
}
void HashTable::delete_nodes(HashNode* node) {
        if (node->next != nullptr)
                delete_nodes(node->next);
        delete node;
}
HashTable::~HashTable() {
        for (int i = 0; i < SIZE; i++) {
                if (this->arr[i] != nullptr)
                        delete_nodes(arr[i]);
        }
}