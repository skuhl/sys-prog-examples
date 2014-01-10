// Scott Kuhl
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* assert() is implemented in the C preprocessor.

   Compile with -DNDEBUG or use "#define NDEBUG" to make assert() do
   nothing. For example, when you are developing a piece of software,
   you might use many, many asserts()---and to get a little bit of
   extra performance out of your program, you might decide to disable
   them.
*/

int main ()
{
	int x = 5;
	// any expressions inside of assert() should be true. If they are
	// false, we exit with a useful error message.
	assert(x < 2);
	return 0;
}
