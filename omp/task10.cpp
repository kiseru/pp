#include <iostream>
#include <omp.h>

int main() {
    int n = 30;
    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }

    int count = 0;
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (a[i] % 3 == 0) {
            #pragma omp atomic
                count++;
        }
    }

    std::cout << count;

    return 0;
}
