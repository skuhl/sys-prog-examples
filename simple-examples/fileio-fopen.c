// Scott Kuhl
//
// Demonstrates using fopen(), fclose(), fseek(), fprintf()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "fileio-fopen.temp"

int main(void)
{
	// "w+" means read+write+create file if it doesn't exist.
	// See "man 3 fopen" for more information.
	FILE *fs = fopen(FILENAME, "w+");
	if(fs == NULL) { perror("fopen"); exit(EXIT_FAILURE); };

	// fprintf(), fseek(), fclose() can all return values indicating
	// an error occurred. We aren't checking for those errors here!
	fprintf(fs, "Hello      \n");
	fseek(fs, -6, SEEK_CUR); // seek backward from our current position.
	fprintf(fs, "world"); // newline will still be there after \n.
	fclose(fs);

	fs = fopen(FILENAME, "r");
	if(fs == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	char c;
	while(fread(&c, 1, 1, fs) > 0)
		printf("%c", c);
	fclose(fs);

	unlink(FILENAME);
	
	return EXIT_SUCCESS;
}
