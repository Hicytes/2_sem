#include <stdio.h>
#include <math.h>

double integral(double a, double b, int N, double (*f)(double)) {
    double h = (b - a) / N;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < N; i++) {
        sum += f(a + i * h);
    }
    
    return sum * h;
}

double constant(double x) { return 1.0; }
double linear(double x) { return 2.0 * x + 3.0; }
double parabola(double x) { return x * x; }
double sine(double x) { return sin(x)- x; }

double exact_constant(double a, double b) { return b - a; }
double exact_linear(double a, double b) { return (b*b - a*a) + 3.0*(b - a); }
double exact_parabola(double a, double b) { return (b*b*b - a*a*a) / 3.0; }
double exact_sine(double a, double b) { return cos(a)- a*a/2.0 - cos(b) + b*b/2.0; }

void investigate(double a, double b, double (*f)(double), 
                double (*exact)(double, double), const char* name) {
    printf("Investigating function: %s\n", name);
    printf("N\tIntegral\tError\t\tI_n - I_2n\tError Reduction\n");
    
    double I = exact(a, b);
    double prev_integral = 0;
    double prev_error = 0;
    
    for (int N = 1; N <= 32; N *= 2) {
        double In = integral(a, b, N, f);
        double error = fabs(In - I);
        
        if (N == 1) {
            printf("%d\t%.10f\t%e\t%s\t%s\n", 
                  N, In, error, "N/A", "N/A");
        } else {
            double diff = fabs(In - prev_integral);
            printf("%d\t%.10f\t%e\t%e\t", N, In, error, diff);
            
            if (N > 2) {
                double reduction = prev_error / error;
                printf("%.2f", reduction);
            } else {
                printf("N/A");
            }
            printf("\n");
        }
        
        prev_integral = In;
        prev_error = error;
    }
    printf("\n");
}

int main() {
    double a = 0.0, b = 1.0;
    
    investigate(a, b, constant, exact_constant, "Constant (1.0)");
    investigate(a, b, linear, exact_linear, "Linear (2x+3)");
    investigate(a, b, parabola, exact_parabola, "Parabola (x^2)");
    investigate(a, b, sine, exact_sine, "Sine (sin(x))");
    
    return 0;
}
