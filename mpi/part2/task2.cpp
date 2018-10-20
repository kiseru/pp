#include <mpich/mpi.h>
#include <iostream>

int **initMatrix(int n, int m);

void printMatrix(int **matrix, int n, int m);

void taskA();

void taskB();

int main() {
    MPI_Init(nullptr, nullptr);
    taskB();
    MPI_Finalize();
    return 0;
}

void taskA() {
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
}

void taskB() {

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    int n = 4;
    int m = 5;

    if (rank == 0) {
        printf("Task B\n");
        int **a = initMatrix(n, m);
        int **b = initMatrix(m, n);

        printf("A:\n");
        printMatrix(a, n, m);
        printf("B:\n");
        printMatrix(b, m, n);

        int **bT = new int *[n];
        for (int i = 0; i < n; i++) {
            bT[i] = new int[m];
            for (int j = 0; j < m; j++) {
                bT[i][j] = b[j][i];
            }
        }

        printf("BT\n");
        printMatrix(bT, n, m);

        for (int i = 1; i < size; i++) {
            MPI_Send(a[i - 1], m, MPI_INT, i, 33, MPI_COMM_WORLD);
            for (int j = 0; j < n; j++) {
                MPI_Send(bT[j], m, MPI_INT, i, 33, MPI_COMM_WORLD);
            }
        }

        int **c = new int *[n];
        for (int i = 0; i < n; i++) {
            c[i] = new int[n];
        }

        for (int i = 1; i < size; i++) {
            MPI_Recv(c[i - 1], n, MPI_INT, i, 33, MPI_COMM_WORLD, &status);
        }

        printf("C:\n");
        printMatrix(c, n, n);
    } else {
        MPI_Probe(0, 33, MPI_COMM_WORLD, &status);

        int amount;
        MPI_Get_count(&status, MPI_INT, &amount);

        printf("amount = %d\n", amount);

        int x[amount];
        MPI_Recv(x, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);

        int result[n];
        for (int j = 0; j < n; j++) {
            result[j] = 0;
        }

        for (int i = 0; i < n; i++) {
            int y[amount];
            MPI_Recv(y, amount, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
            for (int j = 0; j < amount; j++) {
                result[i] += x[j] * y[j];
            }
        }
        MPI_Send(result, n, MPI_INT, 0, 33, MPI_COMM_WORLD);
    }
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