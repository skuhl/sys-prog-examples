// Scott Kuhl
#include <stdio.h>

/* We can figure out how many items are in an array with this
 * macro. 'x' is the array we want the length of. The size of the
 * entire array divided by the size of the individual items in the
 * array tell us how many items are in the array.
 *
 * WARNING: This won't work universally. See the caveat function
 * below. */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


void caveat(int three[], char hello[])
{
	printf("Caveat:\n");
	/* The behavior of sizeof() changes when it is called on an array
	 * that is passed as a parameter. sizeof(three) and sizeof(hello)
	 * will now be the size of a pointer on this machine. */
	printf("items in three: %d / %d = %d\n", (int) sizeof(three), (int) sizeof(three[0]), (int) ARRAY_SIZE(three));
	printf("items in hello: %d / %d = %d\n", (int) sizeof(hello), (int) sizeof(hello[0]), (int) ARRAY_SIZE(hello));
}


int main(void)
{
	int three[3] = { 1, 2, 3 };
	char hello[5] = "hello";

	printf("items in three: %d / %d = %d\n", (int) sizeof(three), (int) sizeof(three[0]), (int) ARRAY_SIZE(three));
	printf("items in hello: %d / %d = %d\n", (int) sizeof(hello), (int) sizeof(hello[0]), (int) ARRAY_SIZE(hello));
	caveat(three, hello);
}



