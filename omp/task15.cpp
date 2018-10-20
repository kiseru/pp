#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;

    double sqrt_n = sqrt(n);

    int prime[n];
    for (int i = 0; i < n; i++) {
        prime[i] = i + 1;
    }

    #pragma omp parallel for
    for (int i = 1; i < (int) sqrt_n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (prime[i] != 0 && prime[j] % prime[i] == 0) {
                #pragma omp critical
                    prime[j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << prime[i] << endl;
    }


    return 0;
}
