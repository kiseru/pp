#include <mpi.h>
#include <iostream>

int main() {
    MPI_Init(NULL, NULL);
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    if (rank == 0) {
        int x[6] = { 1, 3, 7, 0, 9, 8 };
        int y[6] = { 5, 4, 8, 4, 2, 8 };
        for (int i = 1; i < size; i++) {
            MPI_Send(x + (6 / (size - 1)) * (i - 1), 6 / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD);
            MPI_Send(y + (6 / (size - 1)) * (i - 1), 6 / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD);
        }
        int z[6];
        for (int i = 1; i < size; i++) {
            MPI_Recv(z + (6 / (size - 1)) * (i - 1), 6 / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD, &status);
        }
        for (int i = 0; i < 6; i++) {
            printf("%d ", z[i]);
        }
        printf("\n");
    } else {
        MPI_Probe(0, 33, MPI_COMM_WORLD, &status);
        int amount;
        MPI_Get_count(&status, MPI_INT, &amount);
        int x[amount];
        MPI_Recv(x, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
        int y[amount];
        MPI_Recv(y, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
        int z[amount];
        for (int i = 0; i < amount; i++) {
            z[i] = x[i] + y[i];
        }
        MPI_Send(z, amount, MPI_INT, 0, 33, MPI_COMM_WORLD);
    }
    return 0;
}
