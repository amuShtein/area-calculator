#include <stdio.h>

extern double f1 (double a);
extern double f2 (double a);
extern double f3 (double a);

extern double df1dx (double a);
extern double df2dx (double a);
extern double df3dx (double a);

extern double root(double f(double), double g(double), double a, double b, double eps1, int n, ...);
extern int counter;

extern double calc_integral(double f(double), double der(double), double a, double b, double eps2);

extern int print_functions;
extern int print_iterations;

extern void print_formulas();

void test_integral(double eps2) {
	printf("You have entered the test mode of the calc_integral function\n");

	if (print_functions) {
		print_formulas();
	}

	printf("Enter the function number, the lower integration limit, and the upper integration limit\n");
	printf("Example: \"2 1 1.5\" starts counting the integral of the function f2 from 1 to 1.5\n");

	int n;
	double a;
	double b;

	while(scanf("%d %lf %lf", &n, &a, &b) != 3 || n > 3 || n < 0) {
		printf("Incorrect input. Please try again.\n");
	}

	double (*f)(double);
	double (*dfdx)(double);

	switch(n) {
		case 1: f = f1; dfdx = df1dx; break;
		case 2: f = f2; dfdx = df2dx; break;
		case 3: f = f3; dfdx = df3dx; break;
	}

	double integral = calc_integral(f, dfdx, a, b, eps2);

	printf("integral from %.3lf to %.3lf of f%d = %.3lf.\n", a, b, n, integral);
}

void test_root(double eps1) {
	printf("You have entered the test mode of the root function\n");

	if (print_functions) {
		print_formulas();
	}

	printf("Enter the first function number, the second function number, left border, and right border\n");
	printf("Example: \"2 1 1 1.5\" starts counting the point of intersection f2 and f1 on [1, 1.5]\n");

	int n1, n2;
	double a;
	double b;

	while(scanf("%d %d %lf %lf", &n1, &n2, &a, &b) != 4|| n1 > 3 || n1 < 0 || n2 > 3 || n2 < 0) {
		printf("Incorrect input. Please try again.\n");
	}

	double (*f)(double);
	double (*dfdx)(double);

	double (*g)(double);
	double (*dgdx)(double);

	switch(n1) {
		case 1: f = f1; dfdx = df1dx; break;
		case 2: f = f2; dfdx = df2dx; break;
		case 3: f = f3; dfdx = df3dx; break;
	}

	switch(n2) {
		case 1: g = f1; dgdx = df1dx; break;
		case 2: g = f2; dgdx = df2dx; break;
		case 3: g = f3; dgdx = df3dx; break;
	}

	double x = root(f, g, a, b, eps1, 2, dfdx, dgdx);

	if (print_iterations) {
		printf("it took %d iterations to find the intersection point\n", counter);
	}

	printf("Point of intersection of f%d with f%d = (%.4lf, %.4lf)\n", n1, n2, x, f1(x));
}