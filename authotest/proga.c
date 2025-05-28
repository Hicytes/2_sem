#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct MatrixData {
    int M, L, K;
    int **matrix;
};

int handle_error(const char *message) {
    FILE *f = fopen("res.txt", "w");
    if (f != NULL) {
        fprintf(f, "ERROR: %s\n", message);
        fclose(f);
    }
    return -1;
}

int read_data(struct MatrixData *data) {
    FILE *f = fopen("data.txt", "r");
    if (!f) return handle_error("Cannot open data.txt");

    if (fscanf(f, "%d %d %d", &data->M, &data->L, &data->K) != 3) {
        fclose(f);
        return handle_error("Invalid header");
    }

    data->matrix = (int **)malloc(data->L * sizeof(int *));
    if (!data->matrix) {
        fclose(f);
        return handle_error("Memory alloc fail");
    }

    for (int i = 0; i < data->L; ++i) {
        data->matrix[i] = (int *)malloc(data->K * sizeof(int));
        if (!data->matrix[i]) {
            fclose(f);
            return handle_error("Memory alloc fail");
        }

        for (int j = 0; j < data->K; ++j) {
            if (fscanf(f, "%d", &data->matrix[i][j]) != 1) {
                fclose(f);
                return handle_error("Matrix data error");
            }
        }
    }

    fclose(f);
    return 0;
}

bool is_good_column(const struct MatrixData *data, int j) {
    for (int i = 0; i < data->L; ++i)
        if (data->matrix[i][j] % data->M != 0)
            return false;
    return true;
}

void process_matrix(struct MatrixData *data) {
    bool *is_good = calloc(data->K, sizeof(bool));
    if (!is_good) {
        handle_error("Memory alloc fail");
        return;
    }

    int good_count = 0;
    for (int j = 0; j < data->K; ++j) {
        if (is_good_column(data, j)) {
            is_good[j] = true;
            good_count++;
        }
    }

    int *good_cols = malloc(good_count * sizeof(int));
    if (!good_cols) {
        free(is_good);
        handle_error("Memory alloc fail");
        return;
    }

    int idx = 0;
    for (int j = 0; j < data->K; ++j)
        if (is_good[j]) good_cols[idx++] = j;

    for (int i = 0; i < data->L; ++i) {
        for (int a = 0; a < good_count - 1; ++a) {
            for (int b = a + 1; b < good_count; ++b) {
                int ja = good_cols[a], jb = good_cols[b];
                if (abs(data->matrix[i][ja]) > abs(data->matrix[i][jb])) {
                    int t = data->matrix[i][ja];
                    data->matrix[i][ja] = data->matrix[i][jb];
                    data->matrix[i][jb] = t;
                }
            }
        }
    }

    free(is_good);
    free(good_cols);
}

int write_result(const struct MatrixData *data) {
    FILE *f = fopen("res.txt", "w");
    if (!f) return handle_error("Cannot write to res.txt");

    fprintf(f, "%d %d %d\n", data->M, data->L, data->K);
    for (int i = 0; i < data->L; ++i) {
        for (int j = 0; j < data->K; ++j) {
            fprintf(f, "%d%c", data->matrix[i][j], (j == data->K - 1) ? '\n' : ' ');
        }
    }

    fclose(f);
    return 0;
}

int main(void) {
    struct MatrixData data;
    int res;

    if (read_data(&data) != 0) return -1;

    process_matrix(&data);
    res = write_result(&data);

    for (int i = 0; i < data.L; ++i) free(data.matrix[i]);
    free(data.matrix);

    return res;
}

