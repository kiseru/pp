#include <mpich/mpi.h>
#include <iostream>

int main() {
    MPI_Init(nullptr, nullptr);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sizeA[2] = {2, 3};

    if (rank == 0) {
        int a[sizeA[0]][sizeA[1]];
        for (int i = 0; i < sizeA[0]; i++) {
            for (int j = 0; j < sizeA[1]; j++) {
                a[i][j] = rand() % 10;
            }
        }

        printf("A:\n");
        for (int i = 0; i < sizeA[0]; i++) {
            for (int j = 0; j < sizeA[1]; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        int portion = sizeA[0] / (size - 1);

        for (int i = 1; i < size; i++) {
            int portionA[2] = {(i == size - 1 ? sizeA[0] - (i - 1) * portion : portion), sizeA[1]};
            MPI_Send(portionA, 2, MPI_INT, i, 33, MPI_COMM_WORLD);
            MPI_Send(&a[(i - 1) * portion][0], portionA[0] * portionA[1], MPI_INT, i, 33, MPI_COMM_WORLD);
        }

        int sizeB[2] = {sizeA[1], sizeA[0]};
        int b[sizeB[0]][sizeB[1]];

        MPI_Status status;
        for (int i = 0; i < sizeB[0]; i++) {
            for (int j = 1; j < size; j++) {
                int portionB = j == size - 1 ? sizeB[1] - (j - 1) * portion : portion;
                MPI_Recv(&b[i][(j - 1) * portion], portionB, MPI_INT, j, 33, MPI_COMM_WORLD, &status);
            }
        }

        printf("A':\n");
        for (int i = 0; i < sizeB[0]; i++) {
            for (int j = 0; j < sizeB[1]; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Status status;
        int sizeA[2];
        MPI_Recv(sizeA, 2, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
        int a[sizeA[0]][sizeA[1]];
        MPI_Recv(&a, sizeA[0] * sizeA[1], MPI_INT, 0, 33, MPI_COMM_WORLD, &status);
        for (int i = 0; i < sizeA[1]; i++) {
            int buffer[sizeA[0]];
            for (int j = 0; j < sizeA[0]; j++) {
                buffer[j] = a[j][i];
            }
            MPI_Send(buffer, sizeA[0], MPI_INT, 0, 33, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
