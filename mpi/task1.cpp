#include <mpi.h>
#include <iostream>

int main() {
    MPI_Init(NULL, NULL);
    printf("Hello World!\n");
    MPI_Finalize();
    return 0;
}
