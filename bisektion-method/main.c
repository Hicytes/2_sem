#include <stdio.h>
#include <math.h>
#include "bisection.h"
#include "functions.h"
#include <float.h> 
#define MAX_N 25


void analyze(const char* name, double (*f)(double), double a, double b) {
    double x_star = bisection(a, b, 1000, f); 
    double prev = NAN;

    printf("\nFunction: %s\n", name);
    printf("n\t|x_n - x*|\t\t|f(x_n)|\t\t|x_n - x_{n-1}|\n");

    for (int n = 1; n <= MAX_N; ++n) {
        double x_n = bisection(a, b, n, f);
        double fx = f(x_n);
        double err_x = fabs(x_n - x_star);
        double err_f = fabs(fx);
        double delta = isnan(prev) ? DBL_MAX : fabs(x_n - prev);
        prev = x_n;
        printf("%d\t%e\t%e\t%e\n", n, err_x, err_f, delta);
    }
}


int main(){
	int n = 25;
	double a =0.0, b= 1.0;
	/*printf("Enter: n, a, b");
	if(scanf("%d%lf%lf",&n, &a, &b) != 3) return 1;

	if (n <= 0) {
		printf("Error: 'n' must be positive\n");
		return 1;
	}*/

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
	analyze("linear", linear, 0.0, 4.0);
	analyze("quadratic", quadratic, 0.0, 4.0);
	analyze("sine", sine, 0.0, 4.0);
	analyze("tricky", tricky, 0.0, 1.0);

	return 0;
}
