#ifndef GEOMETRY_H
#define GEOMETRY_H

#define EPS 1e-9
#include <stdbool.h>
#include "geometry.h"
#include <stddef.h>

typedef struct {
    double x;
    double y;
} Point;

bool is_point_on_segment(Point p, Point p1, Point p2);
double cross(Point a, Point b, Point c);
bool segment_intersect(Point a, Point b, Point c, Point d);

#endif
