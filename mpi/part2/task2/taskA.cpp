#include <iostream>
#include <mpich/mpi.h>

int **initMatrix(int n, int m);

void printMatrix(int **matrix, int n, int m);

int main() {
    MPI_Init(nullptr, nullptr);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    int n = 4;
    int m = 4;

    if (rank == 0) {
        printf("Task A\n");
        int **a = initMatrix(n, m);
        int **b = initMatrix(n, m);

        printf("A:\n");
        printMatrix(a, n, m);
        printf("B:\n");
        printMatrix(b, n, m);

        for (int i = 1; i < size; i++) {
            MPI_Send(a[i - 1], m, MPI_INT, i, 33, MPI_COMM_WORLD);
            MPI_Send(b[i - 1], m, MPI_INT, i, 33, MPI_COMM_WORLD);
        }

        int **c = new int *[n];
        for (int i = 0; i < n; i++) {
            c[i] = new int[m];
        }

        for (int i = 1; i < size; i++) {
            MPI_Recv(c[i - 1], m, MPI_INT, i, 33, MPI_COMM_WORLD, &status);
        }

        printf("C:\n");
        printMatrix(c, n, m);
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
            z[i] = x[i] * y[i];
        }
        MPI_Send(z, amount, MPI_INT, 0, 33, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

int **initMatrix(int n, int m) {
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void printMatrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

