// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

void func1(void)
{
	printf("hello\n");
}

void func2(void)
{
	printf("world\n");
}

int main(void)
{
	printf("This is main() before we set up the atexit functions.");
	atexit(func1);
	atexit(func2);
	printf("This is main() after we set up the atexit functions.");

	// atexit() does not get called if we interrupt the program with a
	// SIGINT signal (i.e., if we press Ctrl+C while the program is
	// running).
	//
	// sleep(10)

	// To exit without calling the atexit() functions, use abort()
	
	// atexit() gets called if we call exit() or when we return from
	// main().
	exit(EXIT_SUCCESS);
	// return EXIT_SUCCESS;
}
