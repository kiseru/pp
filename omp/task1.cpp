#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        printf("Thread #%d: Amount of thread: %d. Hello, world!\n", omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}