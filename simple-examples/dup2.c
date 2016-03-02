#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



int main(void)
{
	// Create a new file for writing only. Truncate if it exits.
	int file = open("dup2.temp", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if(file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	// Make it so writing to file
	if(dup2(file, STDOUT_FILENO) == -1) // STDOUT_FILENO is 1.
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}

	// Won't print to terminal! Will write to file instead.
	printf("Hello world\n");
	
	// Write message to stderr (because messages written to stdout won't appear!
	fprintf(stderr, "Look in dup2.temp\n");

	return 0;
}
	
