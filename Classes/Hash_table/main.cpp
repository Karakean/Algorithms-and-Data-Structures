#include "HashTable.h"
int main() {
        std::ios::sync_with_stdio(false);
        int value;
        char option;
        std::string name[2], combined;
        HashTable* hash_table = new HashTable();
        while (scanf("%c", &option) != EOF) {
                switch (option)
                {
                case '+':
                        std::cin >> name[0];
                        std::cin >> name[1];
                        combined = name[0] + name[1];
                        scanf("%d", &value);
                        hash_table->insert(combined, value);
                        break;
                case '?':
                        std::cin >> name[0];
                        std::cin >> name[1];
                        combined = name[0] + name[1];
                        hash_table->search(combined);
                        break;
                }
        }
        delete hash_table;
        return 0;
}