#ifndef WELZL_H
#define WELZL_H

#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

Circle welzl(Point* points, int n, Point* boundary, int b);
Circle mec(Point* points, int n);

#endif

