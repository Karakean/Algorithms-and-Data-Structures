#include <iostream>
int find(int x,int*arr,bool mon,int l,int r) {
        while (r >=l) {
        int m = (l + r) / 2;
        if (x == arr[m])return m;
        else if ((x > arr[m] && mon == 1) || (x < arr[m] && mon == 0))return find(x, arr, mon, m+1, r);
        else if ((x < arr[m] && mon == 1) || (x > arr[m] && mon == 0))return find(x, arr, mon, l, m - 1);
        }
        return -1;
}
int main() {
        int m;
        std::cin >> m;
        for (int i = 0;i < m;i++) {
                int n, * s, p, x;
                bool mon;
                std::cin >> n;
                s = new int[n];
                for (int j = 0;j < n;j++) { 
                        std::cin >> s[j];
                }
                if (s[n-1] > s[n - 2])mon = true;
                else if (s[n-1] < s[n - 2])mon = false;
                std::cin >> p;
                for (int j = 0;j < p;j++) {
                        std::cin >> x;
                        std::cout<<find(x,s,mon,0,n-1)<<"\n";
                }
                delete [] s;
        }
        return 0;
}