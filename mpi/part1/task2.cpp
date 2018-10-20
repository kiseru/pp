#include <mpi.h>
#include <iostream>

int main() {
    MPI_Init(NULL, NULL);
    int processes_number;
    MPI_Comm_size(MPI_COMM_WORLD, &processes_number);
    int process_number;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
    printf("Process #%d, number of processes: %d\n", process_number, processes_number);
    MPI_Finalize();
    return 0;
}

