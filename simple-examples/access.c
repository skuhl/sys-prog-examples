// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void checkFile(const char *filename)
{
	printf("\nchecking if file exists: %s\n", filename);
	
	// Note: Remember that a file could be created or deleted
	// immediately after you call access() and before you did
	// something else with the file (such as use open()).
	if(access(filename, F_OK) == 0)
	{
		printf("file exists!\n");
	}
	else
	{
		// many errors could occur (see man page), but if a file
		// doesn't exist, errno would be set to ENOENT.
		perror("access");
	}
}

int main(int argc, char **argv)
{
	(void)argc; // we don't use argc, causes compiler not to warn us about it.
	
	checkFile(argv[0]);
	checkFile("/this/does/not/exist");
	checkFile("/home");
	checkFile("");
	checkFile("/root/test");
	return 0;
}
