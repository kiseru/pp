#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    int vector[3] = {1, 2, 3};

    int result[3]= {0, 0, 0};

    cout << "Sequence variant" << endl;
    double sequence_start = omp_get_wtime();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = matrix[i][j] * vector[j];
        }
    }
    double sequence_stop = omp_get_wtime();

    for (auto &i : result) {
        for (int j : i) {
            cout << j << "|";
        }
        cout << endl;
    }

    cout << "Time passed: " << sequence_stop - sequence_start << endl;

    cout << "Parallel variant" << endl;
    double parallel_start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < 3; i++) {
        //#pragma omp paralles for reduction(+ : result[i])
        for (int j = 0; j < 3; j++) {
            result[i] += matrix[i][j] * vector[j];
            // result[i][j] = matrix[i][j] * vector[j];
        }
    }
    double parallel_stop = omp_get_wtime();

    for (auto &i : result) {
        for (int j : i) {
            cout << j << "|";
        }
        cout << endl;
    }
    cout << "Time passed: " << parallel_stop - parallel_start << endl;

    return 0;
}
