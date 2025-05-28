#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void identity_matrix(double* I, int n) {
    for (int i = 0; i < n * n; ++i) I[i] = 0.0;
    for (int i = 0; i < n; ++i) I[idx(i, i, n)] = 1.0;
}

void mat_mul(double* A, double* B, double* C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            C[idx(i, j, n)] = 0.0;
            for (int k = 0; k < n; ++k)
                C[idx(i, j, n)] += A[idx(i, k, n)] * B[idx(k, j, n)];
        }
}

void mat_sub(double* A, double* B, double* C, int n) {
    for (int i = 0; i < n * n; ++i)
        C[i] = A[i] - B[i];
}

void mat_add(double* A, double* B, double* C, int n) {
    for (int i = 0; i < n * n; ++i)
        C[i] = A[i] + B[i];
}

void mat_copy(double* src, double* dst, int n) {
    for (int i = 0; i < n * n; ++i)
        dst[i] = src[i];
}

void scalar_mul(double* A, double s, double* B, int n) {
    for (int i = 0; i < n * n; ++i)
        B[i] = A[i] * s;
}

void schultz_inverse(double* A, double* invA, int n, int iterations) {
    double *X = malloc(n * n * sizeof(double));
    double *I = malloc(n * n * sizeof(double));
    double *AX = malloc(n * n * sizeof(double));
    double *tmp = malloc(n * n * sizeof(double));

    double* AT = malloc(n * n * sizeof(double));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            AT[idx(j, i, n)] = A[idx(i, j, n)];

    double* ATA = malloc(n * n * sizeof(double));
    mat_mul(AT, A, ATA, n);

    double tr = 0.0;
    for (int i = 0; i < n; ++i)
        tr += ATA[idx(i, i, n)];

    if (fabs(tr) < 1e-12) {
        fprintf(stderr, "Matrix trace too small, possible singular matrix.\n");
        exit(EXIT_FAILURE);
    }

    scalar_mul(AT, 1.0 / tr, X, n);

    identity_matrix(I, n);

    for (int k = 0; k < iterations; ++k) {
        mat_mul(A, X, AX, n);
        mat_sub(I, AX, tmp, n);
        mat_mul(X, tmp, AX, n);
        mat_add(X, AX, tmp, n);
        mat_copy(tmp, X, n);
    }

    mat_copy(X, invA, n);

    free(X); free(I); free(AX); free(tmp); free(AT); free(ATA);
}
