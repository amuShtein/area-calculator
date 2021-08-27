#include <stdio.h>
#include <string.h>
#include <math.h>

#define A_1 0
#define B_1 3

#define A_2 1
#define B_2 1.5

#define A_3 1/4.0
#define B_3 1/3.0

#define MAX_HEIGHT 4.0

#define EPS 0.001
#define EPS1 EPS/(12*MAX_HEIGHT)
#define EPS2 EPS/6

#define HELP_FLAG "-h"
#define LONG_HELP_FLAG "--help"

#define TEST_FLAG "-t"
#define LONG_TEST_FLAG "--test"

#define PRINT_FUNCTIONS_FLAG "-f"
#define ITERATIONS_FLAG "-c"
#define ABSCISSA_FLAG "-x"
#define INTEGRAL_FLAG "-i"

#define TEST_ARG_INTEGRAL "integral"
#define TEST_ARG_ROOT "root"

#define NO_TEST 0
#define ROOT 1
#define INTEGRAL 2

extern double f1 (double a);
extern double f2 (double a);
extern double f3 (double a);

extern double df1dx (double a);
extern double df2dx (double a);
extern double df3dx (double a);

extern double root(double f(double), double g(double), double a, double b, double eps1, int n, ...);
extern int counter;

extern double calc_integral(double f(double), double der(double), double a, double b, double eps2);
extern void print_formulas();

int print_functions = 0;
int print_iterations = 0;
int print_abscisses = 0;
int print_integrals = 0;
int test = NO_TEST;

extern double test_integral (double eps2);
extern double test_root (double eps1);

int main(int ac, char** args) {
	for (int i = 1; i < ac; i++) {
		if (strcmp(args[i], PRINT_FUNCTIONS_FLAG) == 0) {
			print_functions = 1;
		} else if(strcmp(args[i], ITERATIONS_FLAG) == 0) {
			print_iterations = 1;
		} else if(strcmp(args[i], ABSCISSA_FLAG) == 0) {
			print_abscisses = 1;
		} else if(strcmp(args[i], INTEGRAL_FLAG) == 0) {
			print_integrals = 1;
		} else if ((strcmp(args[i], TEST_FLAG) == 0) || (strcmp(args[i], LONG_TEST_FLAG) == 0)) {
			if((ac > i+1) &&  (strcmp(args[i+1], TEST_ARG_INTEGRAL) == 0)) {
				test = INTEGRAL;
				i++;
			} else if( (ac > i+1) &&  (strcmp(args[i+1], TEST_ARG_ROOT) == 0) ) {
				test = ROOT;
				i++;
			} else {
				printf("Error: %s has no arguments\n", args[i]);
			}
		} else if ((strcmp(args[i], HELP_FLAG) == 0) || (strcmp(args[i], LONG_HELP_FLAG) == 0)) {
			printf("_______________FLAGS_______________\n");
			printf("print function formulas\t\t%s\n", PRINT_FUNCTIONS_FLAG);
			printf("print number of iterations\t%s\n", ITERATIONS_FLAG);
			printf("print intersection points\t%s\n", ABSCISSA_FLAG);
			printf("print the calculated integrals\t%s\n", INTEGRAL_FLAG);
			printf("test calc_integral (arg=\"%s\") or root (arg=\"%s\")\t%s\t%s\n",TEST_ARG_INTEGRAL, TEST_ARG_ROOT, TEST_FLAG, LONG_TEST_FLAG);
			printf("example: ./out --test root -f -c\n");
			printf("print info about flags\t\t%s\t%s\n", HELP_FLAG, LONG_HELP_FLAG);
			printf("___________________________________\n");
			return 0;
		} else {
			printf("flag \"%s\" isn't recognized\n", args[i]);
		}
	}

	switch (test) {
			case NO_TEST: break;
			case INTEGRAL: test_integral(EPS2); return 0;
			case ROOT: test_root(EPS1); return 0;
	}

	printf("Finding area between f1, f2 and f3\n");

	if (print_functions) {
		print_formulas();
	}

	double x1_3 = root(f1, f3, A_3, B_3, EPS1, 2, NULL, df3dx);
	if (print_iterations) {
		printf("it took %d iterations to find the intersection point of f1 and f3\n", counter);
	}

	double x1_2 = root(f1, f2, A_1, B_1, EPS1, 2, df1dx, NULL);
	if (print_iterations) {
		printf("it took %d iterations to find the intersection point of f1 and f2\n", counter);
	}

	double x2_3 = root(f2, f3, A_2, B_2, EPS1, 2, df2dx, df3dx);
	if (print_iterations) {
		printf("it took %d iterations to find the intersection point of f2 and f3\n", counter);
	}

	if (print_abscisses) {
		printf("Point of intersection of f1 with f2 = (%.4lf, %.4lf)\n", x1_2, f1(x1_2));
		printf("Point of intersection of f2 with f3 = (%.4lf, %.4lf)\n", x2_3, f2(x2_3));
		printf("Point of intersection of f3 with f1 = (%.4lf, %.4lf)\n", x1_3, f3(x1_3));
	}

	double integral1_2 = calc_integral(f1, df1dx, x1_3, x1_2, EPS2);
	double integral2_3 = calc_integral(f2, df2dx, x1_2, x2_3, EPS2);
	double integral3_1 = calc_integral(f3, df3dx, x2_3, x1_3, EPS2);

	if (print_integrals) {
		printf("integral from %.3lf to %.3lf of f1 = %.3lf\n", x1_3, x1_2, integral1_2);
		printf("integral from %.3lf to %.3lf of f2 = %.3lf\n", x1_2, x2_3, integral2_3);
		printf("integral from %.3lf to %.3lf of f3 = %.3lf\n", x2_3, x1_3, integral3_1);
	}

	double answ = integral1_2 + integral3_1 + integral2_3;

	answ = fabs(answ);

	printf("total area = %.4lf\n", answ);

    return 0;
}