#include <mpi.h>
#include <iostream>

int main() {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 1) {
        int a[10];
        for (int i = 0; i < 10; i++) {
            a[i] = i;
        }
        for (int i = 0; i < size; i++) {
            if (rank == i) continue;

            MPI_Send(a, 10, MPI_INT, i, 33, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        MPI_Probe(1, 33, MPI_COMM_WORLD, &status);
        int amount;
        MPI_Get_count(&status, MPI_INT, &amount);
        int b[amount];
        MPI_Recv(b, amount, MPI_INT, 1, 33, MPI_COMM_WORLD, &status);
        for (int i = 0; i < 10; i++) {
            printf("%d ", b[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
