/* Scott Kuhl

   Checking if the denominator is 0.0f before floating point division
   does not catch all potential problems. First, there are two zeros
   (0.0f and -0.0f). Next, dividing by a subnormal/denormal float can
   also result in infinity. Finally, you may also want to check to see
   if the denominator is NaN. Another approach is to check if the
   result was finite.
*/

#include <stdio.h>
#include <float.h>
#include <math.h>

void checkDivide(float denom)
{
	/* Note, simply checking if denom == 0 will not catch all of the
	 * problems. */
	float result = 1.0 / denom;
	printf("1 / %11g = %11g  -->", denom, result);
	if(isfinite(result))
		printf("division successful\n");
	else
		printf("result is not finite!\n");
}

int main(void)
{
	checkDivide(0.0f);
	checkDivide(-0.0f);
	printf("\n");

	checkDivide(FLT_MIN);
	checkDivide(FLT_MIN/4.0f); /* denormalized or subnormal floating point */
	printf("\n");

	checkDivide(FLT_MAX);
	checkDivide(INFINITY);
	checkDivide(-INFINITY);
	checkDivide(NAN);

	return 0;
}
