#include <iostream>
#include <omp.h>

int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    int sum = 0;

    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < 10; i++) {
        sum += a[i];
    }
    float aAvg = (float) sum / 10;
    printf("Average of a array: %f\n", aAvg);

    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < 10; i++) {
        sum += b[i];
    }
    float bAvg = (float) sum / 10;
    printf("Average of b array: %f\n", bAvg);

    if (aAvg > bAvg) {
        printf("Average of a is grater than average of b");
    } else {
        printf("Average of b is grater than average of a");
    }

    return 0;
}
