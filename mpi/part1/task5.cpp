#include <mpi.h>
#include <iostream>

int main() {
    MPI_Init(NULL, NULL);
    int p;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
    	int a[12];
    	for (int i = 0; i < 12; i++) {
    	    a[i] = i;
    	}
        for (int i = 1; i < p; i++) {
    	    MPI_Send(a + (12 / p) * i, 12 / p, MPI_INT,  i, 33, MPI_COMM_WORLD);
        }
    	for (int i = 0; i < 12 / p; i++) {
    	    printf("Rank #%d: %d\n", rank, a[i]);
    	}
    } else {
        int amount;
        MPI_Status status;
        MPI_Probe(0, 33, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &amount);
        int a[amount];
        MPI_Recv(a, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
        for (int i = 0; i < amount; i++) {
            printf("Rank #%d: %d\n", rank, a[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
