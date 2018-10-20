#include <iostream>
#include <ctime>
#include <omp.h>

int main() {
    std::srand(time(0));
    int d[6][8];

    for (auto &a : d) {
        for (auto &i : a) {
            i = rand();
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int sum = 0;
            for (auto &a : d) {
                for (int i : a) {
                    sum += i;
                }
            }
            double avg = (double) sum / (6 * 8);
            printf("Thread #%d. Average score: %f\n", omp_get_thread_num(), avg);
        }

        #pragma omp section
        {
            int min = d[0][0];
            int max = d[0][0];
            for (auto &a : d) {
                for (int i : a) {
                    if (min > i) {
                        min = i;
                    }
                    if (max < i) {
                        max = i;
                    }
                }
            }
            printf("Thread #%d. Min score: %d. Max score: %d\n", omp_get_thread_num(), min, max);
        }

        #pragma omp section
        {
            int count = 0;
            for (auto &a : d) {
                for (int i : a) {
                    if (i % 3 == 0) {
                        count++;
                    }
                }
            }
            printf("Thread #%d. Number of multiple of three: %d\n", omp_get_thread_num(), count);
        }
    };

    return 0;
}
