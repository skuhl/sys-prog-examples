// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	// If you call wait() and there are not child processes, wait()
	// will return immediately with an error.
	if(wait(NULL) == -1)
	{
		perror("wait");
	}
	return 0;
}
