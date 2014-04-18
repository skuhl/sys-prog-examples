// Scott Kuhl
//
// C99 supports complex numbers.
//
// A listing of available functions:
// https://en.wikipedia.org/wiki/C_mathematical_functions#Complex_numbers
#include <stdio.h>
#include <complex.h>

int main(void)
{
	double complex c = csqrt(-1.0);
	double realPart = creal(c);
	double imagPart = cimag(c);
	printf("sqrt(-1) = %lf + %lf i\n", realPart, imagPart);

	double complex anotherC = 1.0 + 2.0*I;
	printf("Another value = %lf + %lf i\n",
	       creal(anotherC), cimag(anotherC));

	return 0;
}
