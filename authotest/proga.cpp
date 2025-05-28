#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct MatrixData {
    int M, L, K;
    int **matrix;
};

int handle_error(const char *message);
int read_data(MatrixData *data);
bool is_good_column(const MatrixData *data, int j);
void build_S(const MatrixData *data, bool *cols);
void process_matrix(const MatrixData *data, bool *rows, bool *cols);
int write_result(const MatrixData *data);

int handle_error(const char *message) {
    (void)message;
    FILE *f = fopen("res.txt", "w");
    if (f != NULL) {
        fprintf(f, "ERROR\n");
        fclose(f);
    }
    return -1;
}

int read_data(MatrixData *data) {
    FILE *f = fopen("data.txt", "r");
    if (!f) return handle_error("Cannot open data.txt");

    if (fscanf(f, "%d %d %d", &data->M, &data->L, &data->K) != 3) {
        fclose(f);
        return handle_error("Invalid header");
    }

    data->matrix = (int **)malloc(data->L * sizeof(int *));
    if (!data->matrix) return handle_error("Memory alloc fail");

    for (int i = 0; i < data->L; ++i) {
        data->matrix[i] = (int *)malloc(data->K * sizeof(int));
        if (!data->matrix[i]) return handle_error("Memory alloc fail");

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

bool is_good_column(const MatrixData *data, int j) {
    for (int i = 0; i < data->L; ++i) {
        if (data->matrix[i][j] % data->M != 0)
            return false;
    }
    return true;
}

void build_S(const MatrixData *data, bool *cols) {
    for (int j = 0; j < data->K; ++j)
        cols[j] = is_good_column(data, j);
}

void process_matrix(const MatrixData *data, bool *rows, bool *cols) {
    (void)rows;

    for (int i = 0; i < data->L; ++i) {
        int count = 0;
        for (int j = 0; j < data->K; ++j)
            if (cols[j]) count++;

        if (count == 0) continue;

        int *temp = (int *)malloc(count * sizeof(int));
        if (!temp) {
            handle_error("Memory alloc fail");
            return;
        }

        int idx = 0;
        for (int j = 0; j < data->K; ++j)
            if (cols[j])
                temp[idx++] = data->matrix[i][j];

        for (int a = 0; a < count - 1; ++a)
            for (int b = a + 1; b < count; ++b)
                if (abs(temp[a]) > abs(temp[b])) {
                    int t = temp[a];
                    temp[a] = temp[b];
                    temp[b] = t;
                }

        idx = 0;
        for (int j = 0; j < data->K; ++j)
            if (cols[j])
                data->matrix[i][j] = temp[idx++];

        free(temp);
    }
}

int write_result(const MatrixData *data) {
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
    MatrixData data;
    bool *cols, *rows;
    int res;

    if (read_data(&data) != 0) return -1;

    cols = (bool *)calloc(data.K, sizeof(bool));
    rows = (bool *)calloc(data.L, sizeof(bool));
    if (!cols || !rows) return handle_error("Memory error");

    build_S(&data, cols);
    process_matrix(&data, rows, cols);
    res = write_result(&data);

    for (int i = 0; i < data.L; ++i) free(data.matrix[i]);
    free(data.matrix);
    free(cols);
    free(rows);

    return res;
}
