#include <stdio.h>
struct stos {
        bool value;
        stos* next;
};
void start(stos* h) {
        h->next = NULL;
}
void add(stos* s, bool v) {
        stos* n = new stos;
        n->value = v;
        n->next = s->next;
        s->next = n;
}
bool rmv(stos* s) {
                bool a = s->next->value;
                void* x = s->next;
                s->next = s->next->next;
                delete x;
                return a;
}
int main() {
        int n;
        scanf("%d\n", &n);
        for (int i = 0;i < n;i++) {
                char c='\0';
                stos s;
                start(&s);
                while (c!='\n')
                {
                        scanf("%c", &c);
                        if ((c == 't') || (c == 'f')) {
                                bool tmp;
                                if (c == 't')tmp = 1;
                                else tmp = 0;
                                add(&s, tmp);
                        }
                        else if (c == 'N') {
                                bool tmp = rmv(&s);
                                add(&s, !tmp);
                        }
                        else if (c == 'A') {
                                bool tmp1 = rmv(&s);
                                bool tmp2 = rmv(&s);
                                if (tmp1 || tmp2) add(&s, 1);
                                else add(&s, 0);
                        }
                        else if (c == 'K') {
                                bool tmp1 = rmv(&s);
                                bool tmp2 = rmv(&s);
                                if (tmp1 && tmp2) add(&s, 1);
                                else add(&s, 0);
                        }
                }
                bool b = rmv(&s);
                if (b == 1)c = 't';
                else c = 'f';
                printf("%c\n", c);
        }
        return 0;
}