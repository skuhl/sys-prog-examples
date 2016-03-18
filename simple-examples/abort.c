// Scott Kuhl

/* abort() allows you to exit your program. It is typically used if
   your program should exit because of an unusual error. It will send
   the SIGABRT signal to your process.
*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Hello\n");
	abort(); // abort does not call atexit() functions like exit() does. See atexit.c
	printf("World\n");

	return 0;
}
