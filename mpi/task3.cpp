#include <mpi.h>
#include <iostream>

int main() {
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int arr[10];
	for (int i = 0; i < 10; i++) {
	    arr[i] = rand();
	    printf("Process #%d: item[%d] = %d\n", rank, i, arr[i]);
	}
	MPI_Send(arr, 10, MPI_INT, 1, 33, MPI_COMM_WORLD);
    } else if (rank == 1) {
	int arr[10];
	MPI_Recv(arr, 10, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
	for (int i = 0; i < 10; i++) {
	    printf("Process #%d: item[%d] = %d\n", rank, i, arr[i]);
	}
    }
    MPI_Finalize();
    return 0;
}
