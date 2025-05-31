#include <stdio.h>
#include "matrix.h"

int main() {
    int n = 3;
    double A[] = {
        1, 2, 3,
        0, 4, 5,
	0, 0, 6
    };

    double invA[9];
    schultz_inverse(A, invA, n, 10);

    printf("Inverse matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%.6f ", invA[idx(i, j, n)]);
        printf("\n");
    }
    return 0;
}
