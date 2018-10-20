#include <iostream>
#include <omp.h>

int main() {
    int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int b[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        if (thread_num == 0) {
            int min = a[0];
            for (int i = 1; i < 10; i++) {
                if (min > a[i]) {
                    min = a[i];
                }
            }
            printf("Thread #%d: Max item: %d\n", thread_num, min);
        }

        if (thread_num == 1) {
            int max = b[0];
            for (int i = 1; i < 10; i++) {
                if (max < b[i]) {
                    max = b[i];
                }
            }
            printf("Thread #%d: Max item: %d\n", thread_num, max);
        }
    }
}
