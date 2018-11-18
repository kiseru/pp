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
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
        }
    }

    int receivedLine[n];
    MPI_Scatter(a, n, MPI_INT, receivedLine, n, MPI_INT, root, MPI_COMM_WORLD);

    int localSum = 0;
    for (int i = 0; i < n; i++) {
        localSum += abs(receivedLine[i]);
    }
    printf("Local sum: %d. Thread rank: %d.\n", localSum, rank);

    int result;
    MPI_Reduce(&localSum, &result, 1, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Result: %d.\n", result);
    }

    MPI_Finalize();
    return 0;
}
