#include <iostream>
#include <omp.h>

void run(int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        if (omp_get_max_threads() > 1) {
            printf("Thread #%d. Amount of threads: %d.\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }
}

int main() {
    run(3);
    run(1);
    return 0;
}
