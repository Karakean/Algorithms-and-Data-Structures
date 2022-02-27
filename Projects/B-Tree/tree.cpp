#include "Tree.h"
Tree::Tree() {
        this->root = nullptr;
        this->t = NULL;
}
void Tree::setRoot(Node* r) {
        this->root = r;
}
void Tree::setOrder(int _t) {
        this->t = _t;
}
int Tree::calculate(int* arr, int n) {
        int number = 0;
        for (int i = 0; i < n; i++)
                number+= arr[i] * (int)pow(10, n-i-1);
        return number;
}
Node* Tree::load() {
        Node* node = new Node(true, t);
        char input = NULL;
        int keys_counter = 0;
        int sons_counter = 0;
        bool isDigit = false;
        int number[MAX_NUMBER_LENGHT];
        int number_length = 0;
        while ( input != ')') {
                scanf("%c", &input);
                switch (input) {
                case '(':
                        node->sons[sons_counter] = load();
                        sons_counter++;
                        node->isLeaf = false;
                        isDigit = false;
                        break;
                case ')':
                        node->cntKey = keys_counter;
                        isDigit = false;
                        break;
                case ' ':
                        isDigit = false;
                        break;
                case '\n':
                        return node;
                default:
                        number[number_length] = (int)input - 48;
                        number_length++;
                        isDigit = true;
                        break;
                }
                if ((!isDigit) && (number_length > 0)) {
                        node->keys[keys_counter] = calculate(number, number_length);
                        keys_counter++;
                        number_length = 0;
                }
        }
        return node;
}
void Tree::printTree() {
        if (root != nullptr)
                root->print();
        printf("\n");
}
void Tree::treeInsert(int key) {
        if (root != nullptr) {
                if (root->cntKey < 2 * t - 1)
                        root->insert(key);
                else {
                        Node* new_root = new Node(0, t);
                        new_root->sons[0] = root;
                        new_root->split(root, 0);
                        int i = 0;
                        if (new_root->keys[0] < key)
                                i++;
                        new_root->sons[i]->insert(key);
                        root = new_root;
                }
        }
        else {
                root = new Node(1, t);
                root->keys[0] = key;
                root->cntKey++;
        }
}
void Tree::treeSave() {
        printf("%d\n", t);
        if (root != nullptr)
                root->save();
        printf("\n");
}
Node* Tree::treeSearch(int key) {
        if (root != nullptr)
                return root->search(key);
        else
                return nullptr;
}
void Tree::deleteSons(Node* node) {
        int i = 0;
        while (i <= node->cntKey) {
                if (!node->isLeaf) {
                        deleteSons(node->sons[i]);
                        delete node->sons[i];
                }
                i++;
        }
}
Tree::~Tree() {
        deleteSons(root);
        delete root;
}