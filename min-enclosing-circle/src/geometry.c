#include "geometry.h"
#include <math.h>

#define EPS 1e-9

double distance2(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

Circle circle_2_points(Point p1, Point p2) {
    double dist = distance2(p1, p2);
    if (dist <= EPS) return (Circle){(Point){0, 0}, -1};
    return (Circle){(Point){0.5*(p1.x + p2.x), 0.5*(p1.y + p2.y)}, 0.5*sqrt(dist)};
}

Circle circle_3_points(Point p1, Point p2, Point p3) {
    double D = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    if (fabs(D) <= EPS) {
        double d12 = distance2(p1, p2), d23 = distance2(p2, p3), d13 = distance2(p1, p3);
        if (d12 >= d23 && d12 >= d13) return circle_2_points(p1, p2);
        if (d23 >= d12 && d23 >= d13) return circle_2_points(p2, p3);
        return circle_2_points(p1, p3);
    }

    double Ux = ((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) + (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) +
                 (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / D;
    double Uy = ((p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) + (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x) +
                 (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x)) / D;

    Point center = { Ux, Uy };
    double radius = sqrt(distance2(center, p1));

    return (Circle){center, radius};
}

bool point_in_circle(Circle circle, Point p) {
    if (circle.rad < 0) return false;
    return distance2(circle.center, p) <= (circle.rad + EPS) * (circle.rad + EPS);
}

