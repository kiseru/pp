#include <iostream>
#include <mpich/mpi.h>

int main() {
    MPI_Init(nullptr, nullptr);

    int root = 0;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 4;
    int m = 4;
    int a[m][n];
    int b[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i + j + 4;
        }
    }


    int receivedA[n];
    int receivedB[n];
    MPI_Scatter(a, n, MPI_INT, receivedA, n, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(b, n, MPI_INT, receivedB, n, MPI_INT, root, MPI_COMM_WORLD);

    int localResult[n];
    for (int i = 0; i < n; i++) {
        localResult[i] = receivedA[i] * receivedB[i];
    }

    int result[m][n];
    MPI_Gather(localResult, n, MPI_INT, result, n, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("A:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("B:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }

        printf("C:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
