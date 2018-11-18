#include <iostream>
#include <mpich/mpi.h>

int main() {
    MPI_Init(nullptr, nullptr);

    int root = 0;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vectorLength = 4;
    int x[4];
    int y[4];
    for (int i = 0; i < vectorLength; i++) {
        x[i] = i;
        y[i] = i + 4;
    }

    int portion = 2;
    int gotX[2];
    int gotY[2];

    MPI_Scatter(x, portion, MPI_INT, gotX, portion, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(y, portion, MPI_INT, gotY, portion, MPI_INT, root, MPI_COMM_WORLD);

    int localSum = 0;
    for (int i = 0; i < portion; i++) {
        localSum += gotX[i] * gotY[i];
    }
    printf("Local sum: %d. Thread rank: %d.\n", localSum, rank);

    int globalSum;
    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Global sum: %d.\n", globalSum);
    }

    MPI_Finalize();
    return 0;
}
