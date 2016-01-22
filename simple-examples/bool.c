// Scott Kuhl

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	/* Section 7.16 of the C99 standard provides a boolean type. It is
	   named bool (which is a macro that expands to _Bool). 'true' and
	   'false' are also defined (as macros). */
	bool b = false;
	printf("boolean is set to: %d\n", b);
	b = !b;
	printf("boolean is set to: %d\n", b);
	b = 5;
	printf("boolean is set to: %d\n", b);
	
	printf("bytes in a 'bool' type: %zu\n", sizeof(bool));
	/* Why does a bool take up a byte?  The C standard just says that
	   a bool is big enough to contain a 0 and a 1. The smallest
	   addressable object in C is a char (1 byte).

	   See:
	    - Section 6.2.5 of the C99 standard says _Bool must be large
	      enough to hold values 0 and 1 (it leaves open the option of it
	      being larger than that).
	    - http://stackoverflow.com/a/10630231/474549
	*/

	// true is usually typedef'd to 1 (i.e., an integer constant).
	printf("bytes of boolean value 'true': %zu\n", sizeof(true));

	return 0;
}
	
