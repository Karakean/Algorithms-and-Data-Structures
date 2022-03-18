#define _CRT_SECURE_NO_WARNINGS
#define MAX_INSTRUCTION_LENGTH 25
#include <stdio.h>

struct Node {
    int value;
    struct Node* pxn; //xor of previous and next element
};

struct Node* XOR(struct Node* prev, struct Node* next)
{
    return (struct Node*)((uintptr_t)prev ^ (uintptr_t)next);
}

void add_beg(struct Node** head, struct Node** tail, struct Node** actual, struct Node** previous, int value)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->pxn = XOR(*head, NULL);
    if (*head != NULL)
    {
        struct Node* next = XOR((*head)->pxn, NULL);
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

void add_end(struct Node** head, struct Node** tail, struct Node** actual, struct Node** previous, int value)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->pxn = XOR(*tail, NULL);
    if (*tail != NULL)
    {
        struct Node* prev = XOR((*tail)->pxn, NULL);
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

int prev_act(struct Node** actual, struct Node** prev, struct Node** head, struct Node** tail) {
    int itr; //int to return
    if ((*actual) == (*head)) {
        itr = (*tail)->value;
        *actual = *tail;
        *prev = XOR(NULL, (*tail)->pxn);
    }
    else {
        itr = (*prev)->value;
        struct Node* tmp = *actual;
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

int next_act(struct Node** actual, struct Node** prev, struct Node** head, struct Node** tail) {
    int itr; //int to return
    if ((*actual) == (*tail)) {
        itr = (*head)->value;
        *actual = *head;
        *prev = *tail;
    }
    else {
        struct Node* next;
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

void del_beg(struct Node** actual, struct Node** prev, struct Node** head, struct Node** tail) {
    struct Node* ntr = *head;
    if (*head == NULL) {
        return;
    }
    else if ((*head) == (*tail)) { //list contains only one element
        *actual = *prev = *head = *tail = NULL;
    }
    else if ((*head) == (XOR(NULL, (*tail)->pxn))) { //list contains exactly two elements
        (*tail)->pxn = XOR(NULL, NULL);
        *head = *prev = *actual = *tail;
    }
    else { //list contains three elements or more
        struct Node* tmp1;
        struct Node* tmp2;
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
    free(ntr);
}

void del_end(struct Node** actual, struct Node** prev, struct Node** head, struct Node** tail) {
    struct Node* ntr = *tail; //struct Node to remove
    if ((*head) == NULL) {
        return;
    }
    else if ((*head) == (*tail)) {
        *actual = *prev = *head = *tail = NULL;
    }
    else if ((*tail) == (XOR(NULL, (*head)->pxn))) {
        (*head)->pxn = XOR(NULL, NULL);
        *tail = *prev = *actual = *head;
    }
    else {
        struct Node* tmp1;
        struct Node* tmp2;
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
    free(ntr);
}

void add_act(struct Node** actual, struct Node** prev, struct Node** head, int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tmp1;
    new_node->value = value;
    if ((*actual) == (*head)) {
        new_node->pxn = XOR(NULL, *actual);
        tmp1 = XOR(NULL, (*actual)->pxn);
        (*head)->pxn = XOR(new_node, tmp1);
        *prev = *head = new_node;
    }
    else {
        struct Node* tmp2;
        new_node->pxn = XOR(*prev, *actual);
        tmp1 = XOR((*prev)->pxn, *actual);
        tmp2 = XOR((*actual)->pxn, *prev);
        (*prev)->pxn = XOR(tmp1, new_node);
        (*actual)->pxn = XOR(new_node, tmp2);
        *prev = new_node;
    }
}

void del_act(struct Node** actual, struct Node** prev, struct Node** head, struct Node** tail) {
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
        struct Node* pp; //previous previous
        struct Node* next;
        struct Node* nn; //next next
        struct Node* ntr = *actual; //Node to remove
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
        free(ntr);
    }
}

void del_val(struct Node** actual, struct Node** prev, struct Node** head, struct Node** tail, int value) {
    if (*head == NULL) {
        return;
    }
    struct Node* previous = NULL;
    struct Node* curr = *head;
    struct Node* next;
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
                struct Node* ntr = curr;
                struct Node* nn = XOR(curr, next->pxn); //next next
                struct Node* pp = XOR(previous->pxn, curr); //previous previous
                if (curr == *prev) {
                    *prev = XOR(*actual, (*prev)->pxn);
                }
                next->pxn = XOR(previous, nn);
                previous->pxn = XOR(pp, next);
                free(ntr);
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
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* actual = NULL;
    struct Node* prev = NULL;
    char input[MAX_INSTRUCTION_LENGTH];
    int value;
    while (scanf("%s", input)!=EOF) {
        if (!strcmp(input, "ADD_BEG")) {
            scanf("%d", &value);
            add_beg(&head, &tail, &actual, &prev, value);
        }
        else if (!strcmp(input, "ADD_END")) {
            scanf("%d", &value);
            add_end(&head, &tail, &actual, &prev, value);
        }
        else if (!strcmp(input, "PRINT_FORWARD")) {
            print_forward(head);
        }
        else if (!strcmp(input, "PRINT_BACKWARD")) {
            print_backward(tail);
        }
        else if (!strcmp(input, "ACTUAL")) {
            if (actual != NULL) {
                printf("%d\n", actual->value);
            }
            else {
                printf("NULL\n");
            }
        }
        else if (!strcmp(input, "PREV")) {
            if (actual != NULL) {
                printf("%d\n", prev_act(&actual, &prev, &head, &tail));
            }
            else {
                printf("NULL\n");
            }
        }
        else if (!strcmp(input, "NEXT")) {
            if (actual != NULL) {
                printf("%d\n", next_act(&actual, &prev, &head, &tail));
            }
            else {
                printf("NULL\n");
            }
        }
        else if (!strcmp(input, "DEL_BEG")) {
            del_beg(&actual, &prev, &head, &tail);
        }
        else if (!strcmp(input, "DEL_END")) {
            del_end(&actual, &prev, &head, &tail);
        }
        else if (!strcmp(input, "ADD_ACT")) {
            scanf("%d", &value);
            add_act(&actual, &prev, &head, value);
        }
        else if (!strcmp(input, "DEL_ACT")) {
            del_act(&actual, &prev, &head, &tail);
        }
        else if (!strcmp(input, "DEL_VAL")) {
            scanf("%d", &value);
            del_val(&actual, &prev, &head, &tail, value);
        }
    }
    while (tail != NULL) { //freeing memory
        del_beg(&actual, &prev, &head, &tail);
    }
    return (0);
}
