// Scott Kuhl
//
// Demonstrates writing and reading ints from a binary file.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "fileio-binary.temp"

int main(void)
{
	// "w+" means read+write+create file if it doesn't exist.
	// See "man 3 fopen" for more information.
	FILE *fp = fopen(FILENAME, "w+");
	if(fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	int i = (int) getpid();
	fwrite(&i, sizeof(int), 1, fp);
	printf("Wrote %d to file\n", i);
	fclose(fp);

	fp = fopen(FILENAME, "r");
	if(fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	int newI;
	fread(&newI, sizeof(int), 1, fp);
	printf("Read %d from file\n", newI);
	fclose(fp);

	// delete file
	unlink(FILENAME);
	
	return EXIT_SUCCESS;
}
