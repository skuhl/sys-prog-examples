// Scott Kuhl
#include <stdio.h>

int main(void)
{
	// The C standard says that "Between the previous and next
	// sequence point a scalar object shall have its stored value
	// modified once by the evaluation of an expression."

	// What is a sequence point? See:
	// https://en.wikipedia.org/wiki/Sequence_point
	// "int a=b;" has a sequence point at the semicolon.

	// For a more detailed explanation, and more examples, see:
	// http://stackoverflow.com/q/4176328/474549
	int i=10;
	printf("%d\n", i++ * ++i); // undefined
	i = ++i;           // undefined
// ++i = 1;           // undefined: causes gcc compilation error

	// Also, the standard says: "The prior value shall be accessed only
	// to determine the value to be stored."
	int array[] = { 1, 2 };
	array[i] = i++; // undefined
	printf("%d\n", array[0]); // use array variable to prevent warning

	// If we were following the standard, we would only access i to
	// determine which new value we are going to store in i. Here, our
	// access of i in a[i] is not necessary to determine the value
	// that is going to be stored in i (the access to i in i++ is
	// where we do that).


	// Here, we are attempt to print j while also increment j. Much
	// like the previous example, we are accessing j twice within a
	// single sequence point---when it should only be accessed to
	// determine the value to be stored.
	int j=0;
	printf("j=%d\n", j+= 1); // OK, prints 1
	printf("j=%d j=%d\n", j, j += 1);  // undefined

	// In the following example, since we are assigning a value to k,
	// we cannot expect to access it within the sequence point. (If we
	// had only been accessing k to decide what new value to assign to
	// it, it would be OK).
	int k=0;
	printf("k=%d\n", k=10); // OK, prints 10
	printf("k=%d k=%d\n", k, k=20); // undefined

	// When we say the behavior is "undefined", it doesn't necessarily
	// mean that the compiler will just pick one of the "obvious"
	// possibilities. See:
	// http://blog.chris-cole.net/2013/11/30/a-glimpse-of-undefined-behavior-in-c/

}
