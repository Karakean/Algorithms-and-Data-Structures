#include <iostream>
#include <string>
struct number {
        std::string num;
        std::size_t length;
};
bool compare(number fnumber,number snumber) {
        if (fnumber.length > snumber.length)
                return 1;
        else if (fnumber.length < snumber.length)
                return 0;
        else {
                for (std::size_t i = 0;i < fnumber.length;i++) {
                        if ((int)fnumber.num[i] > (int)snumber.num[i])return 1;
                        else if ((int)fnumber.num[i] < (int)snumber.num[i])return 0;
                }
                return 0;
        }
}
void shell_sort(number* numbers, int n) {
        for (int d = n / 2; d >= 1; d /= 2)
        {
                for (int i = d; i < n; i++)
                {
                        number tmp = numbers[i];
                        int j;
                        for (j = i; j >= d && compare(numbers[j - d], tmp) == 1; j -= d) {
                                numbers[j] = numbers[j - d];
                        }
                        numbers[j] = tmp;
                }
        }
}
int main() {
        int n;
        number* numbers;
        std::cin >> n;
        numbers = new number[n];
        for (int i = 0;i < n;i++) {
                std::cin >> numbers[i].num;
                numbers[i].length = (numbers[i].num).length();
        }
        shell_sort(numbers, n);
        for (int i = 0;i < n;i++) {
                std::cout << numbers[i].num << "\n";
        }
        delete[] numbers;
        return 0;
}