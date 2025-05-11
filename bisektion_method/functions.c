#include <math.h>     
#include "functions.h"

double linear(double x) {
	return x * x + 2 * x - 10;
}

double quadratic(double x) {
	return x * x - 4;
}

double sine(double x) {
	return sin(x);
}

double tricky(double x) {
	return cos(x) - x;
}

