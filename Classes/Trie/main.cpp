#include "Node.h"
int main() {
        char input;
        Node* root = new Node();
        while (scanf("%c", &input) != EOF) {
                std::string s;
                std::string t;
                if (input == '+') {
                        std::cin >> s;
                        std::cin >> t;
                        root->addWord(s, t);
                }
                else if (input == '?') {
                        std::cin >> s;
                        Node* tmp = root->search(s);
                        if (tmp != nullptr)
                                std::cout << tmp->getTranslation() << "\n";
                        else
                                printf("-\n");
                }
                else if (input == '*') {
                        std::cin >> s;
                        root->printWords(s);
                }
        }
delete root;
        return 0;
}