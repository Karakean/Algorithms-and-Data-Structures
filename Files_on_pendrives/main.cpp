#include <stdio.h>
struct file {
        int id;
        int size;
};
void file_sort(file* arr, int l, int r) {
        file tmp;
        int i = l;
        int border = l;
        while (i <= r) {
                if (arr[i].size < arr[r].size) {
                        tmp = arr[i];
                        arr[i] = arr[border];
                        arr[border] = tmp;
                        border++;
                }i++;
        }
        tmp = arr[border];
        arr[border] = arr[r];
        arr[r] = tmp;
        if ((border - 1) > l)file_sort(arr, l, border - 1);
        if ((border + 1) < r)file_sort(arr, border + 1, r);
}
void copy(file* arr, file** pendrive, int psize, int n, int *a, int *b) {
        int x = 0;
        int y = 0;
        int sum = 0;
        while (sum <= psize) {
                if (((sum + arr[x].size) > psize) || (x >= n))break;
                sum += arr[x].size;
                x++;
        }
        for (int j = 0;j < x;j++) {
                pendrive[0][j] = arr[j];
        }
        int sum2 = 0;
        while (sum2 <= psize) {
                if (((sum2 + arr[x + y].size) > psize) || ((x + y) >= n))break;
                sum2 += arr[x + y].size;
                y++;
        }
        for (int j = 0;j < y;j++) {
                pendrive[1][j] = arr[x + j];
        }
        *a = x;
        *b = y;
}
void id_sort(file* arr,int l,int r) {
        file tmp;
        int i = l;
        int border = l;
        while (i <= r) {
                if (arr[i].id>arr[r].id) {
                        tmp = arr[i];
                        arr[i] = arr[border];
                        arr[border] = tmp;
                        border++;
                }i++;
        }
        tmp = arr[border];
        arr[border] = arr[r];
        arr[r] = tmp;
        if ((border - 1) > l)id_sort(arr, l, border - 1);
        if ((border + 1) < r)id_sort(arr, border + 1, r);
}
int main()
{
        int n, p;
        file* files;
        file** pendrive;
        scanf("%d", &n);
        scanf("%d", &p);
        files = new file[n];
        pendrive = new file * [2];
        pendrive[0] = new file[n];
        pendrive[1] = new file[n];
        for (int i = 0;i < n;i++) {
                scanf("%d", &files[i].id);
                scanf("%d", &files[i].size);
        }
        file_sort(files, 0, n - 1);
        int a,b;
        copy(files, pendrive, p, n, &a, &b);
        if(a>1)id_sort(pendrive[0], 0, a - 1);
        if(b>1)id_sort(pendrive[1], 0, b - 1);
        int c = a + b;
        printf("%d\n1:",c);
        for (int i = 0;i < a;i++)printf(" %d", pendrive[0][i].id);
        printf("\n2:");
        for (int i = 0;i < b;i++)printf(" %d", pendrive[1][i].id);
        delete[] files;
        delete[] pendrive[0];
        delete[] pendrive[1];
        delete[] pendrive;
        return 0;
}