// Scott Kuhl
#include <stdio.h>
#include <float.h> // for FLT_MIN
#include <stdint.h>


#include <math.h> // for INFINITY and NAN definitions

int main(void)
{
	float tenth = .1; // a repeating number in binary
	float sum = 0;
	// small errors can accumulate over time.
	for(int i=0; i<10000; i++)
		sum += tenth;
	printf("sum (should be 1000 if no rounding errors): %f\n", sum);
	printf("\n");

	// There are two zeros.
	float zero1 =  0.0f;
	float zero2 = -0.0f;
	// Use a union to reliably print out floating point number in hex
	// without compiler warnings. Note that sizeof(float) must be 4
	// bytes for this to work...
	union { float f; uint32_t u; } union1, union2;
	union1.f = zero1;
	union2.f = zero2;
	printf("both zero, two values: 0x%x 0x%x\n", union1.u, union2.u);
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
	printf("The smallest normal float: %f\n", FLT_MIN);
	printf("The smallest normal float (printed with more digits this time): %0.40f\n", FLT_MIN);
	printf("\n");

	// FLT_MIN is the smallest normal float, there are smaller
	// subnormal (aka denormal) floats. For more information,
	// see: http://en.wikipedia.org/wiki/Denormal_number
	float subnormal = FLT_MIN/4.0;
	printf("subnormal is: %0.40f\n", subnormal);
	if(subnormal < FLT_MIN && subnormal > 0)
		printf("subnormal is between 0 and FLT_MIN\n");
	if(!isnormal(subnormal))
		printf("isnormal() verified that subnormal variable is not a normal number\n");
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

	// Also see: isinf(), isfinite(), and fpclassify()
	float inf1=INFINITY;
	float inf2=INFINITY;
	if(inf1 == inf2)
		printf("Infinity == infinity\n");
	else
		printf("Infinity != infinity\n");

	// Also see: isnan(), and fpclassify()
	float nan1 = NAN;
	float nan2 = NAN;
	if(nan1 == nan2)
		printf("NaN == NaN\n");
	else
		printf("NaN != NaN\n");

	if(nan1 == 1.0f)
		printf("NaN == 1.0f\n");
	else
		printf("NaN != 1.0f\n");

	inf1=INFINITY;
	inf2=-INFINITY;
	printf("%f + %f = %f\n", inf1, inf2, inf1+inf2);

	printf("\n");
	printf("a, b, and c \"should\" all be the same value (but might not be since floating-point math isn't associative)\n");
	/* Floating-point math is not associative. For more information, see:
	   http://stackoverflow.com/questions/6430448/
	   The numbers for this example came from:
	   http://cavern.uark.edu/~arnold/4363/FPArith_ex.pdf
	*/
	float val1 =    0.003245678;
	float val2 =  212.3454;
	float val3 = -212.3456;
	float a = val1+val2+val3;
	float b = val1+(val2+val3);
	float c = val3+val2+val1;
	printf("a: %0.40f\n", a);
	printf("b: %0.40f\n", b);
	printf("c: %0.40f\n", c);

	
	printf("\n");
	printf("Denormal/subnormal number example (c \"should\" equal a):\n");
	// This example is based on:
	// https://www.securecoding.cert.org/confluence/display/seccode/FLP05-C.+Don't+use+denormalized+numbers
	a = .543f;
	b = a * 7e-45;
	c = b / 7e-45;
	printf("a=%f\n", a); // prints 0.543000
	printf("b=%f\n", b); // prints 0.000000
	printf("c=%f\n", c); // prints 0.600556 (but you might expect 0.543)
	printf("a %s normal\n", isnormal(a) ? "is" : "is not");
	printf("b %s normal\n", isnormal(b) ? "is" : "is not");
	printf("c %s normal\n", isnormal(c) ? "is" : "is not");
}
