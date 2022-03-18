#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct Stack {
    int value;
    struct Stack* next;
};

void start(struct Stack* h) {
    h->next = NULL;
}

void add(struct Stack* s, int v) {
    struct Stack* n = (struct Stack*)malloc(sizeof(struct Stack));
    n->value = v;
    n->next = s->next;
    s->next = n;
}

int rmv(struct Stack* s) {
    int a = s->next->value;
    void* x = s->next;
    s->next = s->next->next;
    free(x);
    return a;
}

int main() {
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        char c = '\0';
        struct Stack s;
        start(&s);
        while (c != '\n')
        {
            scanf("%c", &c);
            if ((c == 't') || (c == 'f')) {
                int tmp;
                if (c == 't')tmp = 1;
                else tmp = 0;
                add(&s, tmp);
            }
            else if (c == 'N') {
                int tmp = rmv(&s);
                add(&s, !tmp);
            }
            else if (c == 'A') {
                int tmp1 = rmv(&s);
                int tmp2 = rmv(&s);
                if (tmp1 || tmp2) add(&s, 1);
                else add(&s, 0);
            }
            else if (c == 'K') {
                int tmp1 = rmv(&s);
                int tmp2 = rmv(&s);
                if (tmp1 && tmp2) add(&s, 1);
                else add(&s, 0);
            }
        }
        int b = rmv(&s);
        if (b == 1)c = 't';
        else c = 'f';
        printf("%c\n", c);
    }
    return 0;
}
