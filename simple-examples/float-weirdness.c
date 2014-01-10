// Scott Kuhl
#include <stdio.h>
#include <float.h> // for FLT_MIN

#define _GNU_SOURCE
#include <math.h> // for INFINITY and NAN definitions

int main(void)
{
	float tenth = .1; // a repeating number in binary
	float sum = 0;
	// small errors can accumulate over time.
	for(int i=0; i<10000; i++)
		sum += tenth;
	printf("sum: %f\n", sum);
	printf("\n");

	float zero1 =  0.0f;
	float zero2 = -0.0f;
	printf("both zero, two values: 0x%x 0x%x\n", zero1, zero2);
	if(zero1 == zero2)
		printf("The two zeros equal each other.\n");
	else
		printf("The two zeros don't equal each other.\n");
	if(signbit(zero1) == signbit(zero2))
		printf("The two zeros have the same sign bit.\n");
	else
		printf("The two zeros don't have the same sign bit.\n");
		
	printf("\n");

	// There are lots of floats packed in around 0:
	printf("The smallest float: %f\n", FLT_MIN);
	printf("The smallest float (printed with more digits this time): %0.40f\n", FLT_MIN);
	printf("\n");


	// There aren't many floats as you get further from 0
	float big = 10000000000;
	printf("big     = %f\n", big);
	printf("big+1   = %f\n", big+1);
	printf("big+2   = %f\n", big+2);
	printf("big+10  = %f\n", big+10);
	printf("big+100 = %f\n", big+100);
	printf("big+511 = %f\n", big+511);
	printf("big+512 = %f\n", big+512);
	printf("big+1000= %f\n", big+1000);
	printf("\n");

	printf("The largest float:          %f\n", FLT_MAX);
	printf("The largest float + 1:      %f\n", FLT_MAX+1);
	printf("The largest float + 100000: %f\n", FLT_MAX+100000);
	printf("The largest float * 2:      %f\n", FLT_MAX*2);
	printf("isinf(FLT_MAX*2)=%d\n", isinf(FLT_MAX*2));
	float myinf = INFINITY * -1;
	printf("negative infinity?: %f\n", myinf);
	printf("isinf(negative infinity)=%d\n", isinf(myinf));
	float mynan = NAN;
	printf("isnan example: %d\n", isnan(mynan));
	printf("NaN+1= %f\n", mynan+1);
	printf("NaN+negative infinity= %f\n", mynan+myinf);

// http://www.gnu.org/software/libc/manual/html_node/Infinity-and-NaN.html
	// Floating point exception (SIGFPE) may occur when you do these calculations, but you can override that behavior.
	// 1/0 = Infinity
	// log (0) = -Infinity
	// sqrt (-1) = NaN

}
