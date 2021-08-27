#include <stddef.h>
#include <math.h>
#include <stdio.h>

extern double min(double x, double y);
extern double max(double x, double y);
extern double deriv(double f(double), double x0);

int counter = 0;

double (*tmp_f)(double);
double (*tmp_g)(double);

double tmp_dfdx(double x) {
 	return deriv(tmp_f, x);
}

double tmp_dgdx(double x) {
 	return deriv(tmp_g, x);
}

double root(double f(double), double g(double), double a, double b, double eps1, int n, ...) {
	tmp_f = f;
	tmp_g = g;

	double (*dfdx)(double) = tmp_dfdx;
	double (*dgdx)(double) = tmp_dgdx;

	double (**parg1)(double) = (double (**)(double)) (&n + 1); //отталкиваясь от указателя на n вычисляем
	double (**parg2)(double) = (double (**)(double)) (&n + 2); //указатели на опциональные параметры

	double (*arg1)(double); // переменные для хранения
	double (*arg2)(double); // функциональных параметров

	if(n > 0) {
		arg1 = *parg1; // если n хотя бы 1, то получаем первый параметр
		
		if(arg1 != NULL) 
			dfdx = arg1; // если первый параметр не NULL - то это производная f

		if ((n > 1)  && ((arg2 = *parg2) != NULL)) { // если параметров 2, причём второй параметр не NULL
			dgdx = arg2; //то это - производная g
		}
	}

	int der_sign = dfdx((a+b)/2) - dgdx((a+b)/2) > 0 ? 1 : -1;

	int sec_der_sign =  deriv(dfdx, (a+b)/2) - deriv(dgdx, (a+b)/2) > 0 ? 1 : -1;

	double abs_dir_at_a = fabs(dfdx(a) - dgdx(a));

	double abs_dir_at_b = fabs(dfdx(b) - dgdx(b));

	double der_inf = min(abs_dir_at_a, abs_dir_at_b);

	double x = der_sign*sec_der_sign > 0 ? b : a;

	counter = 0;
	
	while (fabs(f(x) - g(x))/der_inf > eps1/2) {
		x = x - (f(x) - g(x))/(dfdx(x) - dgdx(x));
		counter++;
	}

	return x;
}