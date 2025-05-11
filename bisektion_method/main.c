#include <stdio.h>
#include <math.h>
#include "bisection.h"
#include "functions.h"


int main(){
	int n;
	double a, b;
	printf("Enter: n, a, b");
	if(scanf("%d%lf%lf",&n, &a, &b) != 3) return 1;

	if (n <= 0) {
		printf("Error: 'n' must be positive\n");
		return 1;
	}

	double c = bisection(a,b,n,linear);
	double d = bisection(a,b,n,quadratic);
	double e = bisection(a,b,n,sine);
	double f = bisection(a,b,n,tricky);

	double c_error = linear(c);
	double d_error = quadratic(d);
	double e_error = sine(e);
	double f_error = tricky(f);

	printf("Linear root: %lf, Error: %lf\n", c, c_error);
	printf("Quadratic root: %lf, Error: %lf\n", d, d_error);
	printf("Sine root: %lf, Error: %lf\n", e, e_error);
	printf("Tricky root: %lf, Error: %lf\n", f, f_error);

	return 0;
}
