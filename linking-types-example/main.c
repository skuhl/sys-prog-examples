// Scott Kuhl
#include <stdio.h>

/* We have to somehow declare the functions that we want to use from
 * the library. This is needed because the when we compile the program
 * into a .o file, the compiler only looks at this C file---and
 * doesn't look at the library. Therefore, we need to tell the
 * compiler what the names of the other functions are, what they
 * return, and what parameters they take. There are two ways to do
 * this:
 */

// OPTION 1: Declare the functions inline:
//int one(void);
//void two(void);

// OPTION 2: Declare the functions in one or more headers, include them here:
#include "libfoo.h"

int main(int argc, char **argv)
{
	one();
	two();

	return 0;
}
