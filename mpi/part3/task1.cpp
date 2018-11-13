#include <iostream>
#include <mpich/mpi.h>

int main() {
    MPI_Init(nullptr, nullptr);

    int root = 0;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vectorLength = 4;
    int a[vectorLength];
    for (int i = 0; i < vectorLength; i++) {
        a[i] = i;
    }
    int sendingCount = 2;
    int b[sendingCount];

    MPI_Scatter(a, sendingCount, MPI_INT, b, sendingCount, MPI_INT, root, MPI_COMM_WORLD);

    int localSum = 0;
    for (int i = 0; i < sendingCount; i++) {
        localSum += abs(b[i]);
    }
    printf("Local sum: %d. Thread rank: %d.\n", localSum, rank);

    int globalSum;
    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Global sum: %d.\n", globalSum);
    }
}
