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

Circle circle_3_points(Point A, Point B, Point C) {
    double a_x = A.x, a_y = A.y;
    double b_x = B.x, b_y = B.y;
    double c_x = C.x, c_y = C.y;

    double D = (a_x - b_x)*(c_y - b_y) - (a_y - b_y)*(c_x - b_x);

    if (fabs(D) < EPS) {
        double d1 = distance2(A, B);
        double d2 = distance2(A, C);
        double d3 = distance2(B, C);

        if (d1 >= d2 && d1 >= d3) return circle_2_points(A, B);
        if (d2 >= d1 && d2 >= d3) return circle_2_points(A, C);
        return circle_2_points(B, C);
    }

    Point AB = {(a_x + b_x)*0.5, (a_y + b_y)*0.5};
    Point BC = {(c_x + b_x)*0.5, (c_y + b_y)*0.5};
    double C1 = -((b_x - a_x)*AB.x + (b_y - a_y)*AB.y);
    double C2 = -((c_x - b_x)*BC.x + (c_y - b_y)*BC.y);
    double A1 = b_x - a_x, B1 = b_y - a_y;
    double A2 = c_x - b_x, B2 = c_y - b_y;
    double Det = A1*B2 - A2*B1;
    double ux = (-C1*B2 + C2*B1) / Det;
    double uy = (-A1*C2 + A2*C1) / Det;

    Point center = { ux, uy };
    double radius = sqrt(distance2(center, A));

    return (Circle){ center, radius };
}


bool point_in_circle(Circle circle, Point p) {
    if (circle.rad < 0) return false;
    return distance2(circle.center, p) <= circle.rad * circle.rad + EPS;

}

