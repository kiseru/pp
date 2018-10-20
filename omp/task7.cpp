#include <iostream>
#include <omp.h>
#include <string>

using namespace std;

string array_to_string(int a[], int size) {
    string result = "|";
    for (int i = 0; i < size; i++) {
        result += to_string(a[i]) + "|";
    }
    return result;
}

int main() {
    int a[12];
    int b[12];
    int c[12];

    #pragma omp parallel for schedule(static, 4) num_threads(3)
    for (int i = 0; i < 12; i++) {
        printf("Thread #%d. Amount of threads: %d.\n", omp_get_thread_num(), omp_get_num_threads());
        a[i] = i + 1;
        b[i] = i + 13;
    }
    cout << "Array of a = " << array_to_string(a, 12) << endl;
    cout << "Array of b = " << array_to_string(b, 12) << endl;

    #pragma omp parallel for schedule(dynamic, 3) num_threads(4)
    for (int i = 0; i < 12; i++) {
        printf("Thread #%d. Amount of threads: %d.\n", omp_get_thread_num(), omp_get_num_threads());
        c[i] = a[i] + b[i];
    }
    cout << "Array of c = " << array_to_string(c, 12) << endl;

}
