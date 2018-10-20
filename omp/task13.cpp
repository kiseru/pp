#include <iostream>
#include <omp.h>

int pow(int a, int n) {
    if (n == 0) {
        return 1;
    } else if (n % 2 == 1) {
        return a * pow(a, n - 1);
    } else {
        int temp = pow(a, n / 2);
        return temp * temp;
    }
}

int main() {
    int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};

    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < 30; i++) {
        if (a[29 - i] != 0) {
            sum += a[29 - i] * pow(2, i);
        }
    }

    std::cout << sum;

    return 0;
}
