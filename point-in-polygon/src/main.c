#include "geometry.h"
#include "polygon.h"
#include <stdio.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Не удалось открыть файл");
        return 1;
    }

    int count;
    if (fscanf(file, "%d", &count) != 1 || count < 3) {
        printf("Ошибка: в файле должно быть число >= 3\n");
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

    Point p;
    if (fscanf(file, "%lf %lf", &p.x, &p.y) != 2) {
        printf("Ошибка при чтении координат проверяемой точки\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    const char* result = is_point_on_line(p, count, points);
    if (result) {
        printf("%s\n", result);
        return 0;
    }

    result = inside_outside(p, count, points);
    printf("%s\n", result);

    return 0;
}
