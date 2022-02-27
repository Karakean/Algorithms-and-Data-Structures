#include <iostream>
#include <string>
struct Node {
    int value;
    Node* pxn; //xor adresu elementu poprzedniego i nastepnego
};
Node* XOR(Node* a, Node* b)
{
    return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}
void add_beg(Node** head, Node** tail, Node** front, Node** left_front, int value, int* size)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->pxn = XOR(*head, NULL);
    if (*head != NULL)
    {
        Node* next = XOR((*head)->pxn, NULL);
        if (*front == *head) {
            *left_front = new_node;
        }
        (*head)->pxn = XOR(new_node, next);
        *head = new_node;
    }
    else {
        *tail = *head = new_node;
    }
    (*size)++;
}
void add_end(Node** head, Node** tail, Node** back, Node** right_back, int value, int* size)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->pxn = XOR(*tail, NULL);
    if (*tail != NULL)
    {
        Node* prev = XOR((*tail)->pxn, NULL);
        if (*back == *tail) {
            *right_back = new_node;
        }
        (*tail)->pxn = XOR(new_node, prev);
        *tail = new_node;
    }
    else {
        *head = *tail = new_node;
    }
    (*size)++;
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
void del_beg(Node** head, Node** tail, Node** front, Node** left_front, Node** back, Node** right_back, int* size) {
    Node* ntr = *head; //Node to remove
    if (*head == NULL) {
        return;
    }
    else if ((*head) == (*tail)) { //lista jednoelementowa
        *head = *tail = *front = *left_front = *back = *right_back = NULL;
    }
    else if ((*head) == (XOR(NULL, (*tail)->pxn))) { //lista dwuelementowa
        *front = *back = *head = *tail;
        *left_front = *right_back = NULL;
        (*head)->pxn = XOR(NULL, NULL);
    }
    else { //lista trzyelementowa i wieksza
        if ((*back == *head)&&(*back!=*front)) {
            Node* tmp = *back;
            *back = *right_back;
            *right_back = XOR(tmp, (*right_back)->pxn);
        }
        else if ((*front == *head) && (*front != *back)) {
            *front = *tail;
            *left_front = XOR(NULL, (*tail)->pxn);
        }
        else if (*left_front == *head) {
            *left_front = NULL;
        }
        Node* tmp1;
        Node* tmp2;
        tmp1 = XOR(NULL, (*head)->pxn);
        tmp2 = XOR(tmp1->pxn, (*head));
        *head = tmp1;
        (*head)->pxn = XOR(NULL, tmp2);
    }
    delete ntr;
    (*size)--;
}
void del_end(Node** head, Node** tail, Node** front, Node** left_front, Node** back, Node** right_back, int* size) {
    Node* ntr = *tail; //Node to remove
    if ((*head) == NULL) {
        return;
    }
    else if ((*head) == (*tail)) { //lista jednoelementowa
        *head = *tail = *front = *left_front = *back = *right_back = NULL;
    }
    else if ((*tail) == (XOR(NULL, (*head)->pxn))) { //lista dwuelementowa
        *front = *back = *tail = *head;
        *left_front = *right_back = NULL;
        (*tail)->pxn = XOR(NULL, NULL);
    }
    else { //lista trzyelementowa i wieksza
        if ((*front == *tail) && (*tail != *back)) {
            Node* tmp = *front;
            *front = *left_front;
            *left_front = XOR(tmp, (*left_front)->pxn);
        }
        else if ((*back == *tail) && (*back != *front)) {
            *back = *head;
            *right_back = XOR(NULL, (*head)->pxn);
        }
        else if (*right_back == *tail) {
            *right_back = NULL;
        }
        Node* tmp1;
        Node* tmp2;
        tmp1 = XOR(NULL, (*tail)->pxn);
        tmp2 = XOR(tmp1->pxn, *tail);
        *tail = tmp1;
        (*tail)->pxn = XOR(NULL, tmp2);
    }
    delete ntr;
    (*size)--;
}
int count(Node* front, Node* back, Node* left_front, Node* tail) {
    int itr = 0; //int to return
    if (front == NULL) {
        return itr;
    }
    else {
        Node* right = XOR(left_front, front->pxn);
        Node* curr = front;
        Node* left;
        while (curr != back) {
            itr++;
            left = XOR(right, curr->pxn);
            right = curr;
            curr = left;
            if (curr == NULL) {
                curr = tail;
                right = NULL;
            }
        }itr++;
        return itr;
    }
}
void push(Node** head, Node** tail, Node** front, Node** left_front, Node** back, Node** right_back, int value, int* size) {
    int queue_size = count(*front, *back, *left_front, *tail);
    if (*head == NULL) { //pusta lista
        add_beg(head, tail, front, left_front, value, size);
        *front = *back = *head;
    }
    else if (*size==queue_size) {
        Node* new_node = new Node;
        new_node->value = value;
        Node* left_back = XOR(*right_back, (*back)->pxn);
        new_node->pxn = XOR(left_back, *back);
        (*back)->pxn = XOR(new_node, *right_back);
        if (left_back != NULL) {
            Node* left_left_back = XOR(*back, left_back->pxn);
            left_back->pxn = XOR(left_left_back, new_node);
        }
        *right_back = *back;
        *back = new_node;
        if (*head == *right_back) {
            *head = *back;
        }
        if (queue_size == 1) {
            *left_front = new_node;
        }
        (*size)++;
    }
    else {
        if ((*back != *head)&&(queue_size>0)) {
            Node* tmp = *back;
            *back = XOR(*right_back, (*back)->pxn);
            (*back)->value = value;
            *right_back = tmp;
        }
        else {
            *back = *tail;
            (*back)->value = value;
            *right_back = NULL;
            if (*front == NULL) {
                *front = *tail;
                *left_front = XOR(NULL, (*tail)->pxn);
            }
        }
    }
}
int pop(Node** front, Node** left_front, Node** back, Node** right_back, Node** tail) {
    if (count(*front, *back, *left_front, *tail)==0) {
        return -1;
    }
    int itr = (*front)->value; //int to return
    if (*front == *back) {
        *front = *back = *left_front = *right_back = NULL;
    }
    else if (*left_front != NULL) {
        Node* tmp = *front;
        *front = *left_front;
        *left_front = XOR(tmp, (*left_front)->pxn);
    }
    else {
        *front = *tail;
        *left_front = XOR(NULL, (*tail)->pxn);
    }
    return itr;
}
void print_queue(Node* front, Node* back, Node* left_front, Node* tail) {
    if (count(front, back, left_front, tail)==0) {
        printf("NULL\n");
    }
    else {
        Node* prev = XOR(left_front, front->pxn);
        Node* curr = front;
        Node* next;
        while (curr != back) {
            printf("%d ", curr->value);
            next = XOR(prev, curr->pxn);
            prev = curr;
            curr = next;
            if (curr == NULL) {
                curr = tail;
                prev = NULL;
            }
        }
        if (curr == back) {
            printf("%d ", curr->value);
        }
        printf("\n");
    }
}
void garbage_soft(Node** head, Node** tail, Node** front, Node** left_front, Node** back, Node** right_back,int* size) {
    if ((*head == NULL) || (*size == count(*front, *back, *left_front, *tail))) { //pusta lista lub wszystkie elementy listy sa w kolejce
        return;
    }
    else if (*back == NULL) { //pusta kolejka
        Node* prev = NULL;
        Node* curr = *head;
        Node* next;
        while (curr != NULL) {
            curr->value = 0;
            next = XOR(prev, curr->pxn);
            prev = curr;
            curr = next;
        }
    }
    else { //reszta przypadkow
        Node* right = *back;
        Node* curr = XOR(*right_back, (*back)->pxn);
        Node* left;
        while (curr != *front) {
            if (curr == NULL) {
                curr = *tail;
                right = NULL;
            }
            else {
                curr->value = 0;
                left = XOR(right, curr->pxn);
                right = curr;
                curr = left;
            }
        }
    }
}
void garbage_hard(Node** head, Node** tail, Node** front,Node** left_front, Node** back, Node** right_back, int* size) {
    if ((*head == NULL) || (*size == count(*front, *back, *left_front, *tail))) { //pusta lista lub wszystkie elementy listy sa w kolejce
        return;
    }
    else if (*back == NULL) { //pusta kolejka
        while (*tail != NULL) {
            del_beg(head, tail,front,left_front, back, right_back, size);
        }
    }
    else {
        Node* right_right = *right_back; //element na prawo od elementu po prawej od curr
        Node* right = *back; //element po prawej od curr
        Node* curr = XOR(*right_back, (*back)->pxn);
        Node* left; //element po lewej od curr
        Node* left_left; //element na lewo od elementu po lewej od curr
        while (curr != *front) {
            if (curr==NULL) {
                curr = *tail;
                right = NULL;
            }
            else if (curr == *head) {
                del_beg(head, tail, front, left_front, back, right_back, size);
                curr = *tail;
                right = NULL;
            }
            else if (curr == *tail) {
                del_end(head, tail, front, left_front, back, right_back, size);
                curr = *tail;
                right = NULL;
            }
            else { //reszta przypadkow
                Node* ntr = curr; //Node to remove
                left = XOR(right, curr->pxn);
                if (left != NULL) {
                    left_left = XOR(curr, left->pxn);
                    left->pxn = XOR(right, left_left);
                }
                if (right != NULL) {
                    right_right = XOR(curr, right->pxn);
                    right->pxn = XOR(left, right_right);
                }
                curr = left;
                delete ntr;
                (*size)--;
            }
        }
    }
}
int main()
{
    Node* head = NULL;
    Node* tail = NULL;
    Node* front = NULL;
    Node* back = NULL;
    Node* left_front = NULL; //na lewo od front
    Node* right_back = NULL; //na prawo od back
    std::string input;
    int value, size = 0;
    while (std::cin >> input) {
        if (input == "ADD_BEG") {
            std::cin >> value;
            add_beg(&head, &tail, &front, &left_front, value, &size);
        }
        else if (input == "ADD_END") {
            std::cin >> value;
            add_end(&head, &tail, &back, &right_back, value,&size);
        }
        else if (input == "PRINT_FORWARD") {
            print_forward(head);
        }
        else if (input == "PRINT_BACKWARD") {
            print_backward(tail);
        }
        else if (input == "DEL_BEG") {
            del_beg(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
        else if (input == "DEL_END") {
            del_end(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
        else if (input == "SIZE") {
            printf("%d\n", size);
        }
        else if (input == "PUSH") {
            std::cin >> value;
            push(&head, &tail, &front, &left_front, &back, &right_back, value, &size);
        }
        else if (input == "PRINT_QUEUE") {
            print_queue(front, back, left_front, tail);
        }
        else if (input == "COUNT") {
            printf("%d\n", count(front, back, left_front, tail));
        }
        else if (input == "POP") {
            int tmp=pop(&front, &left_front, &back, &right_back, &tail);
            if (tmp == -1) {
                printf("NULL\n");
            }
            else {
                printf("%d\n", tmp);
            }
        }
        else if (input == "GARBAGE_SOFT") {
            garbage_soft(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
        else if (input == "GARBAGE_HARD") {
            garbage_hard(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
    }
    while (tail != NULL) { //zwalnianie pamieci
        del_beg(&head, &tail, &front, &left_front, &back, &right_back, &size);
    }
    return 0;
}
