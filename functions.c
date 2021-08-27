#include <stdio.h>

#define DX 0.00001

#define F1 "exp(-x) + 3"
#define F2 "2x - 2"
#define F3 "1/x"

double min (double x, double y) {
	return (x < y ? x : y);
}

double max (double x, double y) {
	return (x > y ? x : y);
}

double deriv(double f(double), double x0) {
	return (f(x0 + DX) - f(x0 - DX))/(2 * DX);
}

void print_formulas() {
	printf("f1(x) = %s\n", F1);
	printf("f2(x) = %s\n", F2);
	printf("f3(x) = %s\n", F3);
}
