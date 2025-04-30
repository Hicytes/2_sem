#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point center;
    double rad;
} Circle;

double distance2(Point p1, Point p2);
Circle circle_2_points(Point p1, Point p2);
Circle circle_3_points(Point p1, Point p2, Point p3);
bool point_in_circle(Circle circle, Point p);

#endif

