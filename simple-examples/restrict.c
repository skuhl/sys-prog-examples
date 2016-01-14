// Scott Kuhl

/* This example is based on the example provided in the Wikipedia article:
   https://en.wikipedia.org/wiki/Restrict
*/

#include <stdio.h>

void addValueToPointers(int *ptrA, int *ptrB, int *value)
{
	// Take the integer that 'ptrA' points at and add the integer that
	// 'value' points into it.
	*ptrA += *value;
	
	// Do the same for ptrB
	*ptrB += *value;


	/* This solution will work and is correct. The compiler would need to...

	   Determine the integer that 'value' points at.
	   Determine the integer that 'ptrA' points at.
	   Add the two together and store it at the location 'ptrA' points at.

	   Before we handle ptrB, we actually have to determine the
	   integer that 'value' points at again---because it might have
	   changed! If 'ptrA' and 'value' point to the same location, the
	   addition would change both ptrA and value.

	   If we knew that 'value' and 'ptrA' couldn't point to the same
	   spot, the compiler could optimize this better.
	*/
}

void addValueToPointersRestrict(int *restrict ptrA, int *restrict ptrB, int *restrict value)
{
	/* The 'restrict' keyword means that for the lifetime of those
	   variables that are declared with the 'restrict' keyword, only
	   the variable names themselves (or something derived from them
	   using pointer arithmetic) can be used to access the information
	   that they are pointing at. I.e., there are no two pointers that
	   can be used to access the same information.
	*/

	*ptrA += *value;
	*ptrB += *value;

	/* Now, the compiler has the option to optimize this function
	   better because it doesn't have to do the extra work that
	   addValueToPointers() has to do.
	*/
}


int main(void)
{
	int a = 100;
	int b = 200;
	int c = 1;
	printf("Before: a=%d b=%d c=%d\n", a,b,c);
	addValueToPointers(&a, &b, &c);     // works as expected.
	printf("After:  a=%d b=%d c=%d\n", a,b,c);

	a=100,b=200,c=1;
	printf("Before: a=%d b=%d c=%d\n", a,b,c);
	addValueToPointers(&a, &b, &a);     // works as expected.
	printf("After:  a=%d b=%d c=%d\n", a,b,c);

	printf("\n\n");
	
	a=100,b=200,c=1;
	printf("Before: a=%d b=%d c=%d\n", a,b,c);
	addValueToPointersRestrict(&a, &b, &c);     // works as expected.
	printf("After:  a=%d b=%d c=%d\n", a,b,c);

	a=100,b=200,c=1;
	printf("Before: a=%d b=%d c=%d\n", a,b,c);
	/* WRONG. Compiler doesn't have to catch this. The programmer is
	 * expected to notice the restrict keyword and understand the
	 * meaning. */
	addValueToPointersRestrict(&a, &b, &a);
	printf("After:  a=%d b=%d c=%d\n", a,b,c);
}

