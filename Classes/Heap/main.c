#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_NUMBER_OF_ELEMENTS 65536
void swp(int* a, int* b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
}
void heapify(int* arr, int i, int size, bool orientation) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int tmp = i;
        if ((l < size) && (((arr[l] > arr[tmp]) && orientation) || ((arr[l] < arr[tmp]) && !orientation)))
                tmp = l;
        if ((r < size) && (((arr[r] > arr[tmp]) && orientation) || ((arr[r] < arr[tmp]) && !orientation)))
                tmp = r;
        if (tmp != i) {
                swp(&arr[i], &arr[tmp]);
                heapify(arr, tmp, size, orientation);
        }
}
void build_heap(int* arr, int size, bool orientation) {
        for (int i = size / 2 - 1; i >= 0; i--)
                heapify(arr, i, size, orientation);
}
void rev_heapify(int* arr, int i, int size, bool orientation) {
        if (i > 0) {
                int p = (i - 1) / 2;
                if (((arr[i] > arr[p]) && orientation) || ((arr[i] < arr[p]) && !orientation)) {
                        swp(&arr[i], &arr[p]);
                        rev_heapify(arr, p, size, orientation);
                }
        }
}
void add(int* arr, int* size, int v, bool orientation) {
        (*size)++;
        arr[(*size)-1] = v;
        rev_heapify(arr, *size - 1, *size, orientation);
}
int remove(int* arr, int* size, bool orientation) {
        int itr = arr[0]; //int to return
        swp(arr, &arr[(*size) - 1]);
        (*size)--;
        heapify(arr, 0, *size, orientation);
        return itr;
}
int main() {
        char input;
        bool orientation=true; //max heap
        static int arr[MAX_NUMBER_OF_ELEMENTS];
        int size=0;
        bool cond = true;
        while (cond) {
                scanf("%c", &input);
                switch (input)
                {
                case '+':
                        int v;
                        scanf("%d", &v);
                        add(arr, &size, v, orientation);
                        break;
                case '-':
                        printf("%d\n", remove(arr, &size, orientation));
                        break;
                case 'p':
                        for (int i = 0; i < size; i++)
                                printf("%d ", arr[i]);
                        printf("\n");
                        break;
                case 'r':
                        size = 0;
                        int n;
                        scanf("%d", &n);
                        for (int i = 0; i < n; i++) {
                                scanf("%d", &arr[i]);
                                size++;
                        }
                        build_heap(arr, size, orientation);
                        break;
                case 's':
                        orientation = !orientation;
                        build_heap(arr, size, orientation);
                        break;
                case 'q':
                        cond=false;
                        break;
                }
        }
        return 0;
}