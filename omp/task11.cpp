#include <iostream>
#include <omp.h>

int main() {
    int n = 12;
    int a[n];

    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }

    int max = a[0];
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (a[i] % 7 == 0 && a[i] > max) {
            #pragma omp critical
                max = a[i];
        }
    }

    std::cout << max;

    return 0;
}
