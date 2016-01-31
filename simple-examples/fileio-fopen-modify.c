// Scott Kuhl
//
// Demonstrates using fopen(), fclose(), fseek(), fprintf()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "fileio-fopen-modify.temp"

int main(void)
{
	// Write a file (without error checking);
	FILE *fs = fopen(FILENAME, "w");
	fprintf(fs, "Hello world\n");
	fclose(fs);

	// Open the file to read from it (without error checking)
	fs = fopen(FILENAME, "r");

	// delete the file
	unlink(FILENAME);

	// Try to read the file that we opened (but was deleted after we opened it);
	char c;
	while(fread(&c, 1, 1, fs) > 0)
		printf("%c", c);
	fclose(fs);

	return EXIT_SUCCESS;
}
