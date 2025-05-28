#include <math.h>     
#include "functions.h"

double linear(double x) {
	return x - 0.5;
}

double quadratic(double x) {
	return x * x - 0.5;
}

double sine(double x) {
	return sin(x- 0.785);
}

double tricky(double x) {
	return cos(x) - x;
}

