#define _CRT_SECURE_NO_WARNINGS
#define MAX_INSTRUCTION_LENGTH 25
#include <stdio.h>
struct Node {
    int value;
    struct Node* pxn; //xor adresu elementu poprzedniego i nastepnego
};

struct Node* XOR(struct Node* a, struct Node* b)
{
    return (struct Node*)((uintptr_t)a ^ (uintptr_t)b);
}

void add_beg(struct Node** head, struct Node** tail, struct Node** front, struct Node** left_front, int value, int* size)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->pxn = XOR(*head, NULL);
    if (*head != NULL)
    {
        struct Node* next = XOR((*head)->pxn, NULL);
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

void add_end(struct Node** head, struct Node** tail, struct Node** back, struct Node** right_back, int value, int* size)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->pxn = XOR(*tail, NULL);
    if (*tail != NULL)
    {
        struct Node* prev = XOR((*tail)->pxn, NULL);
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

void print_forward(struct Node* head)
{
    if (head == NULL) {
        printf("NULL\n");
    }
    else {
        struct Node* curr = head;
        struct Node* prev = NULL;
        struct Node* next;
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

void print_backward(struct Node* tail)
{
    if (tail == NULL) {
        printf("NULL\n");
    }
    else {
        struct Node* curr = tail;
        struct Node* next = NULL;
        struct Node* prev;
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

void del_beg(struct Node** head, struct Node** tail, struct Node** front, struct Node** left_front, struct Node** back, struct Node** right_back, int* size) {
    struct Node* ntr = *head; //struct Node to remove
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
        if ((*back == *head) && (*back != *front)) {
            struct Node* tmp = *back;
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
        struct Node* tmp1;
        struct Node* tmp2;
        tmp1 = XOR(NULL, (*head)->pxn);
        tmp2 = XOR(tmp1->pxn, (*head));
        *head = tmp1;
        (*head)->pxn = XOR(NULL, tmp2);
    }
    free(ntr);
    (*size)--;
}

void del_end(struct Node** head, struct Node** tail, struct Node** front, struct Node** left_front, struct Node** back, struct Node** right_back, int* size) {
    struct Node* ntr = *tail; //struct Node to remove
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
            struct Node* tmp = *front;
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
        struct Node* tmp1;
        struct Node* tmp2;
        tmp1 = XOR(NULL, (*tail)->pxn);
        tmp2 = XOR(tmp1->pxn, *tail);
        *tail = tmp1;
        (*tail)->pxn = XOR(NULL, tmp2);
    }
    free(ntr);
    (*size)--;
}

int count(struct Node* front, struct Node* back, struct Node* left_front, struct Node* tail) {
    int itr = 0; //int to return
    if (front == NULL) {
        return itr;
    }
    else {
        struct Node* right = XOR(left_front, front->pxn);
        struct Node* curr = front;
        struct Node* left;
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

void push(struct Node** head, struct Node** tail, struct Node** front, struct Node** left_front, struct Node** back, struct Node** right_back, int value, int* size) {
    int queue_size = count(*front, *back, *left_front, *tail);
    if (*head == NULL) { //pusta lista
        add_beg(head, tail, front, left_front, value, size);
        *front = *back = *head;
    }
    else if (*size == queue_size) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->value = value;
        struct Node* left_back = XOR(*right_back, (*back)->pxn);
        new_node->pxn = XOR(left_back, *back);
        (*back)->pxn = XOR(new_node, *right_back);
        if (left_back != NULL) {
            struct Node* left_left_back = XOR(*back, left_back->pxn);
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
        if ((*back != *head) && (queue_size > 0)) {
            struct Node* tmp = *back;
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

int pop(struct Node** front, struct Node** left_front, struct Node** back, struct Node** right_back, struct Node** tail) {
    if (count(*front, *back, *left_front, *tail) == 0) {
        return -1;
    }
    int itr = (*front)->value; //int to return
    if (*front == *back) {
        *front = *back = *left_front = *right_back = NULL;
    }
    else if (*left_front != NULL) {
        struct Node* tmp = *front;
        *front = *left_front;
        *left_front = XOR(tmp, (*left_front)->pxn);
    }
    else {
        *front = *tail;
        *left_front = XOR(NULL, (*tail)->pxn);
    }
    return itr;
}

void print_queue(struct Node* front, struct Node* back, struct Node* left_front, struct Node* tail) {
    if (count(front, back, left_front, tail) == 0) {
        printf("NULL\n");
    }
    else {
        struct Node* prev = XOR(left_front, front->pxn);
        struct Node* curr = front;
        struct Node* next;
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

void garbage_soft(struct Node** head, struct Node** tail, struct Node** front, struct Node** left_front, struct Node** back, struct Node** right_back, int* size) {
    if ((*head == NULL) || (*size == count(*front, *back, *left_front, *tail))) { //pusta lista lub wszystkie elementy listy sa w kolejce
        return;
    }
    else if (*back == NULL) { //pusta kolejka
        struct Node* prev = NULL;
        struct Node* curr = *head;
        struct Node* next;
        while (curr != NULL) {
            curr->value = 0;
            next = XOR(prev, curr->pxn);
            prev = curr;
            curr = next;
        }
    }
    else { //reszta przypadkow
        struct Node* right = *back;
        struct Node* curr = XOR(*right_back, (*back)->pxn);
        struct Node* left;
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

void garbage_hard(struct Node** head, struct Node** tail, struct Node** front, struct Node** left_front, struct Node** back, struct Node** right_back, int* size) {
    if ((*head == NULL) || (*size == count(*front, *back, *left_front, *tail))) { //pusta lista lub wszystkie elementy listy sa w kolejce
        return;
    }
    else if (*back == NULL) { //pusta kolejka
        while (*tail != NULL) {
            del_beg(head, tail, front, left_front, back, right_back, size);
        }
    }
    else {
        struct Node* right_right = *right_back; //element na prawo od elementu po prawej od curr
        struct Node* right = *back; //element po prawej od curr
        struct Node* curr = XOR(*right_back, (*back)->pxn);
        struct Node* left; //element po lewej od curr
        struct Node* left_left; //element na lewo od elementu po lewej od curr
        while (curr != *front) {
            if (curr == NULL) {
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
                struct Node* ntr = curr; //struct Node to remove
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
                free(ntr);
                (*size)--;
            }
        }
    }
}

int main()
{
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* front = NULL;
    struct Node* back = NULL;
    struct Node* left_front = NULL; //na lewo od front
    struct Node* right_back = NULL; //na prawo od back
    char input[MAX_INSTRUCTION_LENGTH];
    int value, size = 0;
    while (scanf("%s", input) != EOF) {
        if (!strcmp(input, "ADD_BEG")) {
            scanf("%d", &value);
            add_beg(&head, &tail, &front, &left_front, value, &size);
        }
        else if (!strcmp(input, "ADD_END")) {
            scanf("%d", &value);
            add_end(&head, &tail, &back, &right_back, value, &size);
        }
        else if (!strcmp(input, "PRINT_FORWARD")) {
            print_forward(head);
        }
        else if (!strcmp(input, "PRINT_BACKWARD")) {
            print_backward(tail);
        }
        else if (!strcmp(input, "DEL_BEG")) {
            del_beg(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
        else if (!strcmp(input, "DEL_END")) {
            del_end(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
        else if (!strcmp(input, "SIZE")) {
            printf("%d\n", size);
        }
        else if (!strcmp(input, "PUSH")) {
            scanf("%d", &value);
            push(&head, &tail, &front, &left_front, &back, &right_back, value, &size);
        }
        else if (!strcmp(input, "PRINT_QUEUE")) {
            print_queue(front, back, left_front, tail);
        }
        else if (!strcmp(input, "COUNT")) {
            printf("%d\n", count(front, back, left_front, tail));
        }
        else if (!strcmp(input, "POP")) {
            int tmp = pop(&front, &left_front, &back, &right_back, &tail);
            if (tmp == -1) {
                printf("NULL\n");
            }
            else {
                printf("%d\n", tmp);
            }
        }
        else if (!strcmp(input, "GARBAGE_SOFT")) {
            garbage_soft(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
        else if (!strcmp(input, "GARBAGE_HARD")) {
            garbage_hard(&head, &tail, &front, &left_front, &back, &right_back, &size);
        }
    }
    while (tail != NULL) { //zwalnianie pamieci
        del_beg(&head, &tail, &front, &left_front, &back, &right_back, &size);
    }
    return 0;
}
