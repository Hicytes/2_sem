#include <stdio.h>
#include "matrix.h"

int main() {
    int n = 2;
    double A[] = {
        4, 7,
        2, 6
    };

    double invA[4];
    schultz_inverse(A, invA, n, 10);

    printf("Inverse matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%.6f ", invA[idx(i, j, n)]);
        printf("\n");
    }
    return 0;
}
