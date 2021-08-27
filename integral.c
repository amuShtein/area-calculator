#include <math.h>

extern double min(double x, double y);
extern double max(double x, double y);
extern double deriv(double f(double), double x0);


double calc_integral(double f(double), double der(double), double a, double b, double eps2) {
	int sign = 1;

	if(a > b) {
		a = a + b;
		b = a - b;
		a = a - b;

		sign = -1;
	}

	double sum = 0;

	/* Так как для классического метода нужна вторая производная, 
	мы приблизительно вычисляем её по функции f'(x), которую
	мы получаем в качестве второго параметра */

	double d2fd2x_a = deriv(der, a); //вычисляем f''(x) в точках
	double d2fd2x_b = deriv(der, b); //a и b 

	double m = max(fabs(d2fd2x_a), fabs(d2fd2x_b)); // m = max{|f''(a)|, |f''(b)|}

	double len = fabs(b-a);

	int n = (int)sqrt((m*len*len*len)/(12*eps2)); //считаем n - количество отрезков разбиения
	n++;										  //такое, чтобы погрешность была < eps2
	
	double x = a;
	double delta = len/n;

	for(int k = 1; k < n; k++) {
		x = a + len*k/n;
		sum += f(x);
	}

	sum = (sum*2 + f(a) + f(b))*len/(2*n);

	sum *= sign;

	return sum;
}

