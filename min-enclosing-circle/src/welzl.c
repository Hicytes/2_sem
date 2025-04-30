#include "welzl.h"
#include "random.h"
#include "geometry.h"
#include <string.h>

Circle welzl(Point* points, int n, Point* boundary, int b) {
    if (n == 0 || b == 3) {
        if (b == 0) return (Circle){ {0, 0}, -1 }; 
        if (b == 1) return (Circle){ boundary[0], 0 }; 
        if (b == 2) return circle_2_points(boundary[0], boundary[1]);  
        return circle_3_points(boundary[0], boundary[1], boundary[2]);
    }

    int i = (int)(xoroshiro128plus() % n);
    Point p = points[i];
    points[i] = points[n - 1];

    Circle c = welzl(points, n - 1, boundary, b);

    if (point_in_circle(c, p)) return c;

    boundary[b] = p;

    return welzl(points, n - 1, boundary, b + 1);
}

Circle mec(Point* points, int n) {
    if (n == 0) return (Circle){ {0, 0}, -1 };  
    if (n == 1) return (Circle){ points[0], 0 };  

    Point* points_copy = malloc(n * sizeof(Point));
    if (!points_copy) {
        perror("Не удалось выделить память");
        return (Circle){ {0, 0}, -1 };
    }

    memcpy(points_copy, points, n * sizeof(Point));

    Point boundary[3];
    Circle result = welzl(points_copy, n, boundary, 0);

    free(points_copy);
    return result;
}

