// Scott Kuhl
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* assert() is implemented in the C preprocessor.

   Compile with -DNDEBUG or use "#define NDEBUG" to make assert() do
   nothing. For example, when you are developing a piece of software,
   you might use many, many asserts()---and to get a little bit of
   extra performance out of your program, you might decide to disable
   them. Some production programs ship with assertions turned on! */

int main ()
{
	// Change the x variable to change the behavior of this program.
	int x = 1;
	
	// Any expressions inside of assert() should be true. If they are
	// false, we will exit with an error message indicating the file
	// and line number that the problem occurred at.
	assert(x < 2);

	// If you want even more helpful messages when an assertion fails,
	// try this:
	assert(x == 1 && "This is a clever way to print an informative message whenever an assert fails.");

	// Don't change the state of your program (i.e., change a
	// variable, call a function that changes the state of your
	// program). If your assert() call changes the state of your
	// program, compiling with assert() turned off will change the
	// behavior of your program.
	// assert(x=9); // don't do this!
	

	exit(0);
	// Indicate that some code is unreachable:
	assert(0 && "We hit an unreachable location.");

	return 0;
}
