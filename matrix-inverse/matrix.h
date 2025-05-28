#ifndef MATRIX_H
#define MATRIX_H

void identity_matrix(double* I, int n);
void mat_mul(double* A, double* B, double* C, int n);
void mat_sub(double* A, double* B, double* C, int n);
void mat_add(double* A, double* B, double* C, int n);
void mat_copy(double* src, double* dst, int n);
void scalar_mul(double* A, double s, double* B, int n);
void schultz_inverse(double* A, double* invA, int n, int iterations);

static inline int idx(int i, int j, int n) {
    return i * n + j;
}

#endif
