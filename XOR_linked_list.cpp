#include <iostream>
#include <string>
struct Node {
    int value;
    Node* pxn; //xor adresu elementu poprzedniego i nastepnego
};
Node* XOR(Node* prev, Node* next)
{
    return (Node*)((uintptr_t)prev ^ (uintptr_t)next);
}
void add_beg(Node** head, Node** tail, Node** actual, Node** previous, int value)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->pxn = XOR(*head, NULL);
    if (*head != NULL)
    {
        Node* next = XOR((*head)->pxn, NULL);
        (*head)->pxn = XOR(new_node, next);
        *head = new_node;
        if (*previous == *tail) {
            *previous = *head;
        }
    }
    else {
        *previous = *actual = *tail = *head = new_node;
    }
}
void add_end(Node** head, Node** tail, Node** actual, Node** previous, int value)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->pxn = XOR(*tail, NULL);
    if (*tail != NULL)
    {
        Node* prev = XOR((*tail)->pxn, NULL);
        (*tail)->pxn = XOR(new_node, prev);
        *tail = new_node;
        if (*actual == *head) {
            *previous = *tail;
        }
    }
    else {
        *previous = *actual = *head = *tail = new_node;
    }
}
void print_forward(Node* head)
{
    if (head == NULL) {
        printf("NULL\n");
    }
    else {
        Node* curr = head;
        Node* prev = NULL;
        Node* next;
        while (curr != NULL)
        {
            printf("%d ", curr->value);
            next = XOR(prev, curr->pxn);
            prev = curr;
            curr = next;
        }
        printf("\n");
    }
}
void print_backward(Node* tail)
{
    if (tail == NULL) {
        printf("NULL\n");
    }
    else {
        Node* curr = tail;
        Node* next = NULL;
        Node* prev;
        while (curr != NULL)
        {
            printf("%d ", curr->value);
            prev = XOR(curr->pxn, next);
            next = curr;
            curr = prev;
        }
        printf("\n");
    }
}
int prev_act(Node** actual, Node** prev, Node** head, Node** tail) {
    int itr; //int to return
    if ((*actual) == (*head)) {
        itr = (*tail)->value;
        *actual = *tail;
        *prev = XOR(NULL, (*tail)->pxn);
    }
    else {
        itr = (*prev)->value;
        Node* tmp = *actual;
        *actual = *prev;
        if ((*actual) != (*head)) {
            *prev = XOR(tmp, (*actual)->pxn);
        }
        else {
            *prev = *tail;
        }
    }
    return itr;
}
int next_act(Node** actual, Node** prev, Node** head, Node** tail) {
    int itr; //int to return
    if ((*actual) == (*tail)) {
        itr = (*head)->value;
        *actual = *head;
        *prev = *tail;
    }
    else {
        Node* next;
        if ((*actual) != (*head)) {
            next = XOR(*prev, (*actual)->pxn);
        }
        else {
            next = XOR(NULL, (*actual)->pxn);
        }
        itr = next->value;
        *prev = *actual;
        *actual = next;
    }
    return itr;
}
void del_beg(Node** actual, Node** prev, Node** head, Node** tail) {
    Node* ntr = *head;
    if (*head == NULL) {
        return;
    }
    else if ((*head) == (*tail)) { //lista jednoelementowa
        *actual = *prev = *head = *tail = NULL;
    }
    else if ((*head) == (XOR(NULL, (*tail)->pxn))) { //lista dwuelementowa
        (*tail)->pxn = XOR(NULL, NULL);
        *head = *prev = *actual = *tail;
    }
    else { //lista trzyelementowa i wieksza
        Node* tmp1;
        Node* tmp2;
        tmp1 = XOR(NULL, (*head)->pxn);
        tmp2 = XOR(tmp1->pxn, (*head));
        if ((*actual) == (*head)) {
            *head = tmp1;
            *actual = *prev;
            *prev = XOR(NULL, (*tail)->pxn);
        }
        else if ((*prev) == (*head)) {
            *prev = *tail;
            *head = tmp1;
        }
        else {
            *head = tmp1;
        }
        (*head)->pxn = XOR(NULL, tmp2);
    }
    delete ntr;
}
void del_end(Node** actual, Node** prev, Node** head, Node** tail) {
    Node* ntr = *tail; //Node to remove
    if ((*head) == NULL) {
        return;
    }
    else if ((*head) == (*tail)) { //lista jednoelementowa
        *actual = *prev = *head = *tail = NULL;
    }
    else if ((*tail) == (XOR(NULL, (*head)->pxn))) { //lista dwuelementowa
        (*head)->pxn = XOR(NULL, NULL);
        *tail = *prev = *actual = *head;
    }
    else { //lista trzyelementowa i wieksza
        Node* tmp1;
        Node* tmp2;
        tmp1 = XOR(NULL, (*tail)->pxn);
        tmp2 = XOR(tmp1->pxn, *tail);
        if ((*actual) == (*tail)) {
            *actual = *prev;
            *prev = tmp2;
            *tail = *actual;
        }
        else if ((*prev) == (*tail)) {
            *prev = tmp1;
            *tail = *prev = tmp1;
        }
        else {
            *tail = tmp1;
        }
        (*tail)->pxn = XOR(NULL, tmp2);
    }
    delete ntr;
}
void add_act(Node** actual, Node** prev, Node** head, int value) {
    Node* new_node = new Node;
    Node* tmp1;
    new_node->value = value;
    if ((*actual) == (*head)) {
        new_node->pxn = XOR(NULL, *actual);
        tmp1 = XOR(NULL, (*actual)->pxn);
        (*head)->pxn = XOR(new_node, tmp1);
        *prev = *head = new_node;
    }
    else {
        Node* tmp2;
        new_node->pxn = XOR(*prev, *actual);
        tmp1 = XOR((*prev)->pxn, *actual);
        tmp2 = XOR((*actual)->pxn, *prev);
        (*prev)->pxn = XOR(tmp1, new_node);
        (*actual)->pxn = XOR(new_node, tmp2);
        *prev = new_node;
    }
}
void del_act(Node** actual, Node** prev, Node** head, Node** tail) {
    if ((*head) == NULL) {
        return;
    }
    else if (*actual == *head) {
        del_beg(actual, prev, head, tail);
    }
    else if (*actual == *tail) {
        del_end(actual, prev, head, tail);
    }
    else {
        Node* pp; //previous previous
        Node* next;
        Node* nn; //next next
        Node* ntr = *actual; //Node to remove
        pp = XOR(*actual, (*prev)->pxn);
        next = XOR(*prev, (*actual)->pxn);
        nn = XOR(*actual, next->pxn);
        (*prev)->pxn = XOR(pp, next);
        next->pxn = XOR(*prev, nn);
        if ((*prev) == (*head)) {
            *actual = *head;
            *prev = *tail;
        }
        else {
            *actual = *prev;
            *prev = pp;
        }
        delete ntr;
    }
}
void del_val(Node** actual, Node** prev, Node** head, Node** tail, int value) {
    if (*head == NULL) {
        return;
    }
    Node* previous = NULL;
    Node* curr = *head;
    Node* next;
    while (curr != NULL) {
        next = XOR(previous, curr->pxn);
        if (curr->value == value) {
            if (curr == *head) {
                del_beg(actual, prev, head, tail);
            }
            else if (curr == *tail) {
                del_end(actual, prev, head, tail);
            }
            else if (curr == *actual) {
                del_act(actual, prev, head, tail);
            }
            else {
                Node* ntr = curr;
                Node* nn = XOR(curr, next->pxn); //next next
                Node* pp = XOR(previous->pxn, curr); //previous previous
                if (curr == *prev) {
                    *prev = XOR(*actual, (*prev)->pxn);
                }
                next->pxn = XOR(previous, nn);
                previous->pxn = XOR(pp, next);
                delete ntr;
            }
            curr = NULL;
        }
        if (curr != NULL) {
            previous = curr;
        }
        curr = next;
    }
}
int main()
{
    Node* head = NULL;
    Node* tail = NULL;
    Node* actual = NULL;
    Node* prev = NULL;
    std::string input;
    int value;
    while (std::cin >> input) {
        if (input == "ADD_BEG") {
            std::cin >> value;
            add_beg(&head, &tail, &actual, &prev, value);
        }
        else if (input == "ADD_END") {
            std::cin >> value;
            add_end(&head, &tail, &actual, &prev, value);
        }
        else if (input == "PRINT_FORWARD") {
            print_forward(head);
        }
        else if (input == "PRINT_BACKWARD") {
            print_backward(tail);
        }
        else if (input == "ACTUAL") {
            if (actual != NULL) {
                printf("%d\n", actual->value);
            }
            else {
                printf("NULL\n");
            }
        }
        else if (input == "PREV") {
            if (actual != NULL) {
                printf("%d\n", prev_act(&actual, &prev, &head, &tail));
            }
            else {
                printf("NULL\n");
            }
        }
        else if (input == "NEXT") {
            if (actual != NULL) {
                printf("%d\n", next_act(&actual, &prev, &head, &tail));
            }
            else {
                printf("NULL\n");
            }
        }
        else if (input == "DEL_BEG") {
            del_beg(&actual, &prev, &head, &tail);
        }
        else if (input == "DEL_END") {
            del_end(&actual, &prev, &head, &tail);
        }
        else if (input == "ADD_ACT") {
            std::cin >> value;
            add_act(&actual, &prev, &head, value);
        }
        else if (input == "DEL_ACT") {
            del_act(&actual, &prev, &head, &tail);
        }
        else if (input == "DEL_VAL") {
            std::cin >> value;
            del_val(&actual, &prev, &head, &tail, value);
        }
    }
    while (tail != NULL) { //zwalnianie pamieci
        del_beg(&actual, &prev, &head, &tail);
    }
    return (0);
}
