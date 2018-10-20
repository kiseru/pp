#include <iostream>
#include <omp.h>

int main() {
    int n = 6;
    int m = 8;
    int d[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            d[i][j] = rand() % 100;
        }
    }

    int max = d[0][0];
    int min = d[0][0];
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (max < d[i][j]) {
                #pragma omp critical
                {
                    if (max < d[i][j]) {
                        max = d[i][j];
                    }
                };
            }
            if (min > d[i][j]) {
                #pragma omp critical
                {
                    min = d[i][j];
                };
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

    printf("Min item in matrix: %d. Max item in matrix: %d.", min, max);

    return 0;
}
