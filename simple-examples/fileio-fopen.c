// Scott Kuhl
//
// Demonstrates using fopen(), fclose(), fseek(), fprintf()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "fileio-fopen.temp"

int main(void)
{
	// "w+" means write+create file if it doesn't exist.
	// See "man 3 fopen" for more information.
	FILE *fs = fopen(FILENAME, "w+");
	if(fs == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	// fprintf(), fseek(), fclose() can all return values indicating
	// an error occurred. We aren't checking for those errors here!

	// Write "hello" with extra stuff after it.
	fprintf(fs, "Hello      , you are nice.\n");

	// Seek backward in the file---to one space after "hello"
	fseek(fs, -21, SEEK_CUR);

	// Write "world" in the space that we left.
	fprintf(fs, "world");
	fclose(fs); // close the file.

	//-----------------

	// Read the file that we just wrote and print it to the console.
	fs = fopen(FILENAME, "r");
	if(fs == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	char c;
	while(fread(&c, 1, 1, fs) > 0)
		printf("%c", c);
	fclose(fs);

	unlink(FILENAME); // delete the file
	
	return EXIT_SUCCESS;
}
