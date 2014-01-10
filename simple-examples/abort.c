// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Hello\n");
	abort(); // abort does not call atexit() functions like exit() does. See atexit.c
	printf("World\n");

	return 0;
}
