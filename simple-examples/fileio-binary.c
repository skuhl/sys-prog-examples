/* Scott Kuhl

   readWriteInts(): Demonstrates writing (and reading) integers to
   (and from) a binary file.

   readWriteBytes(): Demonstrates writing (and reading) bytes to
   (and from) a binary file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "fileio-binary.temp"

/* This function writes an int (typically 32 bits) to a file. Then, it
 * reads the int back from the file. The value written to the file
 * should match the value read from the file. */
void readWriteInts(void)
{
	/* "w" means write (and truncate any existing file to 0 bytes)
	   
	   "+" allows us to read too.
	   
	   "b" isn't used by POSIX compliant systems like Linux but may be
	   necessary for other systems.
	
	   See "man 3 fopen", the C99 specification, or the POSIX
	   specification for more information.

	   The following page also describes some of the differences
	   between binary and non-binary streams according to the C
	   standard:
	   https://www.securecoding.cert.org/confluence/display/c/FIO14-C.+Understand+the+difference+between+text+mode+and+binary+mode+with+file+streams
	*/
	FILE *fp = fopen(FILENAME, "wb");
	// Verify we opened the file
	if(fp == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	/* Get the process id for this process (i.e., basically a random
	 * int). */
	int i = (int) getpid();

	/* Write the int to the file. It may be wise to check the return
	   value of fwrite() and fread()! */
	fwrite(&i, sizeof(int), 1, fp);
	printf("Wrote %d to file\n", i);
	fclose(fp); // Finish writing to file.

	// ------------------
	
	// Open the file for reading, verify that we can open it.
	fp = fopen(FILENAME, "r");
	if(fp == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	// Read the integer from the file.
	int newI;
	fread(&newI, sizeof(int), 1, fp);
	printf("Read %d from file\n", newI);
	fclose(fp); // Finish reading from the file.
}


/* Write a series of bytes to the file. Then, read the bytes back from
 * the file. */
void readWriteBytes(void)
{
	/* Note: Both "uint8_t" (from #include <stdint.h>) and "unsigned
	   char" are guaranteed to be 1 byte and be unsigned (i.e., they'd
	   allow for values ranging from 0 to 255). */

	/* The data to write to the file. Note that we can use characters,
	   decimal numbers, or hexadecimal---all are valid ways to specify
	   a value from 0 to 255. */
	unsigned char bytes[5] = { 'a', '*', 0x0F, 10, 255 };

	// Open the file for writing, check for errors.
	FILE *fp = fopen(FILENAME, "wb");
	if(fp == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	// Write the bytes to the file.
	for(int i=0; i<5; i++)
	{
		// It may be wise to check the return value of fwrite() and
		// fread()
		fwrite(&bytes[i], 1, 1, fp);
		printf("Wrote '%d' to file which is character '%c' and hex 0x%x\n",
		       bytes[i], bytes[i], bytes[i]);
	}
	fclose(fp); // Finished writing to file, close the file.
	
	// ------------------
	
	// Open the file for reading, verify we opened it successfully.
	fp = fopen(FILENAME, "r");
	if(fp == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	// Read the bytes from the file.
	char c = '?';
	for(int i=0; i<5; i++)
	{
		fread(&c, 1, 1, fp);
		printf("Read '%d' from file which is character '%c' and hex 0x%x\n",
		       c, c, c);
	}
	fclose(fp); // Finished reading from file. Closing it.
}


int main(void)
{
	readWriteInts();
	printf("\n\n");
	readWriteBytes();
	
	remove(FILENAME); // delete file
	
	return EXIT_SUCCESS;
}
