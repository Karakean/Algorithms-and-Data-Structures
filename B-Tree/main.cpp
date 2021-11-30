#include "Tree.h"
int main() {
        Tree* tree = new Tree();
        char input=NULL;
        int order;
        while (input != 'X') {
                int value;
                Node* tmp;
                scanf("%c", &input);
                switch (input)
                {
                case 'I':
                        scanf("%d", &order);
                        tree->setOrder(order);
                        break;
                case 'A':
                        scanf("%d", &value);
                        tree->treeInsert(value);
                        break;
                case '?':
                        scanf("%d", &value);
                        tmp = tree->treeSearch(value);
                        if (tmp != nullptr)
                                printf("%d +\n", value);
                        else
                                printf("%d -\n", value);
                        break;
                case 'P':
                        tree->printTree();
                        break;
                case 'L':
                        scanf("%d\n(", &order);
                        tree->setOrder(order);
                        tree->setRoot(tree->load());
                        break;
                case 'S':
                        tree->treeSave();
                        break;
                case 'X':
                        break;
                }
        }
        delete tree;
        return 0;
}