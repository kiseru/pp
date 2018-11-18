#include <iostream>
#include <mpich/mpi.h>

int main() {
    MPI_Init(nullptr, nullptr);

    int root = 0;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int m = 4;
    int n = 4;
    int a[m][n];
    int x[n];

    for (int i = 0; i < n; i++) {
        x[i] = i + 4;
        for (int j = 0; j < m; j++) {
            a[j][i] = i + j;
        }
    }

    int receivedPartOfMatrix[n];
    MPI_Scatter(a, n, MPI_INT, receivedPartOfMatrix, n, MPI_INT, root, MPI_COMM_WORLD);

    MPI_Bcast(x, n, MPI_INT, root, MPI_COMM_WORLD);

    int localResult = 0;
    for (int i = 0; i < n; i++) {
        localResult += receivedPartOfMatrix[i] * x[i];
    }

    int z[m];
    MPI_Gather(&localResult, 1, MPI_INT, z, 1, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("A:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("x: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", x[i]);
        }
        printf("\n");

        printf("z: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", z[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

