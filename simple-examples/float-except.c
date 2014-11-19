// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <fenv.h>

int main(void)
{
	printf("Dividing by zero (first time)\n");
	volatile float a = 1.0f, b=0.0f;
	volatile float c = a/b;
	printf("Result: %f\n", c);

	// Turns on SIGFPE signal for divide by zero, overflow, underflow,
	// etc.
	feenableexcept(FE_ALL_EXCEPT); // Linux only!

	printf("Dividing by zero (second time)\n");
	c = a/b;
	printf("Result: %f (we shouldn't get here)\n", c);
}	
