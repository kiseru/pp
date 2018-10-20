#include <mpi.h>
#include <iostream>

const int a = 3;
const int b = 4;

void addition(int *x, int *y, int *z, int length);
void multiplication(int *x, int *y, int *z, int length);
void printArray(int *x, int length);

int main() {
    int n = 4;

    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    if (rank == 0) {
        int x[n];
        int y[n];
        for (int i = 0; i < n; i++) {
            x[i] = rand() % 10;
            y[i] = rand() % 10;
        }
	
	printf("x: ");
        printArray(x, n);

	printf("y: ");
        printArray(y, n);

        for (int i = 1; i < size; i++) {
            MPI_Send(x + (n / (size - 1)) * (i - 1), n / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD);
            MPI_Send(y + (n / (size - 1)) * (i - 1), n / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD);
        }

        int z[n];

        for (int i = 1; i < size; i++) {
            MPI_Recv(z + (n / (size - 1)) * (i - 1), n / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD, &status);
        }
	printf("Addition: ");
        printArray(z, n);

	for (int i = 1; i < size; i++) {
            MPI_Recv(z + (n / (size - 1)) * (i - 1), n / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD, &status);
	}
	printf("Multiplication: ");
	printArray(z, n);

	for (int i = 1; i < size; i++) {
	    MPI_Recv(x + (n / (size - 1)) * (i - 1), n / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD, &status);
	    MPI_Recv(y + (n / (size - 1)) * (i - 1), n / (size - 1), MPI_INT, i, 33, MPI_COMM_WORLD, &status);
	}
	printf("x: ");
	printArray(x, n);
	printf("y: ");
	printArray(y, n);
    } else {
        MPI_Probe(0, 33, MPI_COMM_WORLD, &status);

        int amount;
        MPI_Get_count(&status, MPI_INT, &amount);

        int x[amount];
        MPI_Recv(x, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);

        int y[amount];
        MPI_Recv(y, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);

        int z[amount];

        addition(x, y, z, amount);
        MPI_Send(z, amount, MPI_INT, 0, 33, MPI_COMM_WORLD);

	multiplication(x, y, z, amount);
	MPI_Send(z, amount, MPI_INT, 0, 33, MPI_COMM_WORLD);

	MPI_Send(y, amount, MPI_INT, 0, 33, MPI_COMM_WORLD);
	MPI_Send(x, amount, MPI_INT, 0, 33, MPI_COMM_WORLD);
    }
    return 0;
}

void addition(int *x, int *y, int *z, int length) {
    for (int i = 0; i < length; i++) {
        z[i] = a * x[i] + b * y[i];
    }
}

void multiplication(int *x, int *y, int *z, int length) {
    for (int i = 0; i < length; i++) {
        z[i] = x[i] * y[i];
    }
}

void printArray(int *x, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}
