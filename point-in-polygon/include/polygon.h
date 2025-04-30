#ifndef POLYGON_H
#define POLYGON_H

#include "geometry.h"

const char* is_point_on_line(Point p, int count, Point* points);
const char* inside_outside(Point p, int count, Point* points);

#endif
