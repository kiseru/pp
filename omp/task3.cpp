#include <iostream>
#include <omp.h>

int main() {
    int a = 3;
    int b = 4;
    printf("Before first region: a = %d, b = %d.\n", a, b);
    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int thread_num = omp_get_thread_num();
        printf("Thread #%d before computations. a = %d, b = %d.\n", thread_num, a, b);
        a += thread_num;
        b += thread_num;
        printf("Thread #%d after computations. a = %d, b = %d.\n", thread_num, a, b);
    }
    printf("After first region and before second region: a = %d, b = %d.\n", a, b);
    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int thread_num = omp_get_thread_num();
        printf("Thread #%d before computations. a = %d, b = %d.\n", thread_num, a, b);
        a -= thread_num;
        b -= thread_num;
        printf("Thread #%d after computations. a = %d, b = %d.\n", thread_num, a, b);
    }
    printf("After second region: a = %d, b = %d.\n", a, b);
}
