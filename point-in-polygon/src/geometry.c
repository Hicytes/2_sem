#include "geometry.h"
#include <math.h>

double cross(Point a, Point b, Point c) {

        return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);

}

bool segment_intersect(Point a, Point b, Point c, Point d) {

        double d1 = cross(a, b, c);
        double d2 = cross(a, b, d);
        double d3 = cross(c, d, a);
        double d4 = cross(c, d, b);

        if (((d1 > EPS && d2 < -EPS) || (d1 < -EPS && d2 > EPS)) &&
        ((d3 > EPS && d4 < -EPS) || (d3 < -EPS && d4 > EPS)))

                return true;

        if (fabs(d1) < EPS && is_point_on_segment(c, a, b)) return true;
        if (fabs(d2) < EPS && is_point_on_segment(d, a, b)) return true;
        if (fabs(d3) < EPS && is_point_on_segment(a, c, d)) return true;
        if (fabs(d4) < EPS && is_point_on_segment(b, c, d)) return true;

        return false;
}

bool is_point_on_segment(Point p, Point p1, Point p2){
        double area = (p1.x - p.x)*(p2.y - p.y) - (p2.x - p.x)*(p1.y - p.y);
        if (fabs(area) > EPS)
                return false;

        if (fmin(p1.x, p2.x) - EPS <= p.x && p.x <= fmax(p1.x, p2.x) + EPS &&
        fmin(p1.y, p2.y) - EPS <= p.y && p.y <= fmax(p1.y, p2.y) + EPS)
                return true;

        return false;
}
