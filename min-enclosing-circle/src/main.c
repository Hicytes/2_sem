#include "welzl.h"
#include "random.h"
#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    seed_rng_auto();
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Не удалось открыть файл");
        return 1;
    }

    int count;
    if (fscanf(file, "%d", &count) != 1 || count < 1) {
        printf("Ошибка: в файле должно быть число >= 1\n");
        fclose(file);
        return 1;
    }

    Point points[count];
    for (int i = 0; i < count; i++) {
        if (fscanf(file, "%lf %lf", &points[i].x, &points[i].y) != 2) {
            printf("Ошибка при чтении координат точки %d\n", i + 1);
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    Circle mec_circle = mec(points, count);
    if (mec_circle.rad < 0) {
        printf("Ошибка: не удалось построить окружность\n");
        return 1;
    }

    printf("Минимальная охватывающая окружность:\n");
    printf("Центр: (%.6f, %.6f)\n", mec_circle.center.x, mec_circle.center.y);
    printf("Радиус: %.6f\n", mec_circle.rad);

    return 0;
}

