// Scott Kuhl
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int main(void) {
	printf("We are pid %d\n", getpid());
	printf("The session ID for this terminal %d\n", tcgetsid(0));
	printf("The process group for this terminal %d\n", tcgetpgrp(0));
	exit(EXIT_SUCCESS);
}
