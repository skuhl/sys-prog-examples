// Scott Kuhl
//
// Demonstrates writing and reading ints from a binary file.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "fileio-binary.temp"

void readWriteInts(void)
{
	/* "w" means write (and truncate any existing file to 0 bytes)
	   
	   "+" allows us to read too.
	   
	   "b" isn't used by POSIX compliant systems like Linux but may be necessary for other systems.
	
	   See "man 3 fopen", the C99 specification, or the POSIX specification for more information.
	*/
	FILE *fp = fopen(FILENAME, "w+");
	if(fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	int i = (int) getpid();
	// It may be wise to check the return value of fwrite() and fread()!
	fwrite(&i, sizeof(int), 1, fp);
	printf("Wrote %d to file\n", i);
	fclose(fp);

	fp = fopen(FILENAME, "r");
	if(fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	int newI;
	fread(&newI, sizeof(int), 1, fp);
	printf("Read %d from file\n", newI);
	fclose(fp);
}


void readWriteBytes(void)
{
	/* Both "uint8_t" (from #include <stdint.h>) and
	   "unsigned char" are guaranteed to be 1 byte and be unsigned
	   (i.e., they'd allow for values ranging from 0 to 255. */

	// The data to write to the file. Note that we can use characters,
	// decimal numbers, or hexadecimal---all are valid ways to specify
	// a value from 0 to 255.
	unsigned char bytes[5] = { 'a', '*', 0x0F, 10, 255 };
	FILE *fp = fopen(FILENAME, "w+");
	if(fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	for(int i=0; i<5; i++)
	{
		// It may be wise to check the return value of fwrite() and
		// fread()
		fwrite(&bytes[i], 1, 1, fp);
		printf("Wrote '%d' to file which is character '%c' and hex 0x%x\n", bytes[i], bytes[i], bytes[i]);
	}
	fclose(fp);

	// Read the data back in from the file:
	fp = fopen(FILENAME, "r");
	if(fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); };
	char c = '?';
	for(int i=0; i<5; i++)
	{
		fread(&c, 1, 1, fp);
		printf("Read '%d' from file which is character '%c' and hex 0x%x\n", c, c, c);
	}
	fclose(fp);
}


int main(void)
{
	readWriteInts();
	printf("\n\n");
	readWriteBytes();

    // delete file
	unlink(FILENAME);
	
	return EXIT_SUCCESS;
}
