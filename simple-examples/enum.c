// Scott Kuhl
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	typedef enum { SLOW, NORMAL, FAST, FASTEST } speed;

	printf("SLOW=%d\n", SLOW);
	printf("NORMAL=%d\n", NORMAL);
	printf("FAST=%d\n", FAST);
	printf("FASTEST=%d\n", FASTEST);

	speed s = SLOW;
	s=s+1;
	if(s == NORMAL)
		printf("s is now NORMAL\n");

	// Values can be explicitly assigned to enumeration constants. If
	// values have a power of 2, then each enum value corresponds to a
	// bit. Then, you can use & and | to combine and examine which
	// bits are set.
	typedef enum {
		TALL = 1,
		CLEVER = 2,
		BIG  = 4,
	} flags;
	
	flags f = TALL|CLEVER;
	if(f & TALL)
		printf("f has the TALL bit set\n");

	return 0;
}
