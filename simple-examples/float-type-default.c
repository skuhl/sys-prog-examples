// Scott Kuhl
#include <stdio.h>

int main(void)
{
	// This program probably doesn't produce any warnings unless you
	// use the -Wfloat-conversions flag with gcc.
	double d = .3;   // a double assigned to a double
	double df = .3f; // a float  assigned to a double
	float f = .3;    // a double assigned to a float
	float ff = .3f;  // a float  assigned to a float

	// See printf-formatting.c for a more details about why we can use
	// the same formatting string for floats and doubles.
	printf("%.40f\n", d);
	printf("%.40f\n", df);
	printf("%.40f\n", f);
	printf("%.40f\n", ff);

	/* Why does this matter? */

	printf(".3 (float)  * 3.1 (float)  = %.40f\n", f * 3.1f);
	printf(".3 (float)  * 3.1 (double) = %.40f\n", f * 3.1); // f is promoted to a double before the multiplication takes place.
	printf(".3 (double) * 3.1 (double) = %.40f\n", 0.3 * 3.1);
	// Each of the three lines above prints different values!

	// Summary:
	// If you don't specify that a number is a float, the compiler
	// assumes that it is double---forcing the math to occur at a
	// higher precision than what might be necessary. This can impact
	// the performance of your program and change the value that
	// results from your calculations.
}
