#include <stdio.h>

int find(int x, int* arr, int mon, int l, int r) {
    while (r >= l) {
        int m = (l + r) / 2;
        if (x == arr[m])return m;
        else if ((x > arr[m] && mon == 1) || (x < arr[m] && mon == 0))
            return find(x, arr, mon, m + 1, r);
        else if ((x < arr[m] && mon == 1) || (x > arr[m] && mon == 0))
            return find(x, arr, mon, l, m - 1);
    }
    return -1;
}

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int n, p, x;
        int* s;
        int mon;
        scanf("%d", &n);
        s = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", s[j]);
        }
        if (s[n - 1] > s[n - 2])
            mon = 1;
        else
            mon = 0;
        scanf("%d", &p);
        for (int j = 0; j < p; j++) {
            scanf("%d", &x);
            printf("%d\n", find(x, s, mon, 0, n - 1));
        }
        free(s);
    }
    return 0;
}
