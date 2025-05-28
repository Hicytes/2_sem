#include "bisection.h"
#include <math.h>

double bisection(double a, double b, int n, double (*f)(double)){
	double fa = f(a);
	double fb = f(b);

	if (fa * fb > 0) return NAN;
	if (fabs(fa) < EPS) return a;
	if (fabs(fb) < EPS) return b;
	
	double c = (a + b)/2, fc = f(c);
	for(int i=0; i < n; i++){
                if (fabs(fc) < EPS) return c;
		if(fa*fc > 0){a = c; fa = fc;} else {b = c; fb = fc;}
		c = (a + b)/2;
	}
	return c;
}
