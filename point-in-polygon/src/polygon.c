#include "polygon.h"
#include <math.h>

const char* is_point_on_line(Point p, int count, Point* points){

        for(int i = 0; i < count; i++){
                int j = (i + 1) % count;
                if (is_point_on_segment(p, points[i], points[j]))
                        return "Точка на границе";
        }

        return NULL;

}

const char* inside_outside(Point p, int count, Point* points){

        double min_x = points[0].x, max_x = points[0].x;
        double min_y = points[0].y, max_y = points[0].y;
        for(int i = 1; i < count; i++){

                if (min_x > points[i].x) min_x = points[i].x;
                if (max_x < points[i].x) max_x = points[i].x;
                if (min_y > points[i].y) min_y = points[i].y;
                if (max_y < points[i].y) max_y = points[i].y;

        }

        if (p.x < min_x - EPS || p.x > max_x + EPS || p.y < min_y - EPS || p.y > max_y + EPS)
                return "Точка снаружи";

        Point out = {1e9, p.y};

        int intersections = 0;

        for(int i = 0; i < count; i++){

                int j = (i + 1) % count;
                if (segment_intersect(p, out, points[i], points[j]))
                        intersections++;

        }

        if (intersections % 2 == 1)
                return "Точка внутри";
        else
                return "Точка снаружи";

}

