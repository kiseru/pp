#include <iostream>
#include <omp.h>

int main() {
    int n = 210;

    int result = 0;
    #pragma omp parallel for reduction(+ : result)
    for (int i = 1; i < 2 * n; i += 2) {
        result += i;
    }

    std::cout << result;

    return 0;
}
