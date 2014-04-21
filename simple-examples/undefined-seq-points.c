// Scott Kuhl
#include <stdio.h>

int main(void)
{
	// The C standard says that "Between the previous and next
	// sequence point a scalar object shall have its stored value
	// modified once by the evaluation of an expression.

	// What is a sequence point? See:
	// https://en.wikipedia.org/wiki/Sequence_point
	// "int a=b;" has a sequence point at the semicolon.

	// For a more detailed explanation, and more examples, see:
	// http://stackoverflow.com/q/4176328/474549
	int i=10;
	printf("%d\n", i++ * ++i); // undefined
	i = ++i;           // undefined
// ++i = 1;           // undefined: causes gcc compilation error

	// Also, the standard says: The prior value shall be accessed only
	// to determine the value to be stored.
	int array[] = { 1, 2 };
	array[i] = i++; // undefined
	printf("%d\n", array[0]); // use array variable to prevent warning

	// If we were following the standard, we would only access i to
	// determine which new value we are going to store in i. Here, our
	// access of i in a[i] is not being accessed to determine the
	// value to be stored in i (i++).

	// When we say the behavior is "undefined", it doesn't necessarily
	// mean that the compiler will just pick one of the "obvious"
	// possibilities. See:
	// http://blog.chris-cole.net/2013/11/30/a-glimpse-of-undefined-behavior-in-c/

}
