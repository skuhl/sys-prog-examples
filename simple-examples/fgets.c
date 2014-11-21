// Scott Kuhl

/* This file demonstrates some of the nuances and details of reading
 * binary files with fgets(). In general fread() may be easier to use!
 *
 * Run the program, read the comments, look at fgets.temp using xxd.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FILENAME "fgets.temp"

int main(void)
{
	// Write some bytes to the file. Note that the 4th byte is a null
	// byte.
	FILE *fp = fopen(FILENAME, "w");
	char list[] = { '0', '0', '0', '\0',
	                'e', 'o', 'f', -1,
	                'n', 'e', 'w', '\n',
	                'e', 'n', 'd', 'X' };
	printf("writing %lu bytes to fgets.temp; please view it with xxd.\n", sizeof(list));
	fwrite(list, sizeof(list), 1, fp);
	fclose(fp);

	/* Print the size of the file in bytes */
	struct stat s;
	stat(FILENAME, &s);
	printf("file size is: %u\n", (int) s.st_size);

	/* Try to read the file we just created. */
	fp = fopen(FILENAME, "r");
	
	// fgets will read until a newline or end of the file and
	// terminates what it read with a null character---but it doesn't
	// tell you how many characters were read. So, if you reach a '\0'
	// (null character) in the file, you don't know for sure if it is
	// part of the file or if it is the null character that fgets put
	// at the end of the bytes it read. In text files, there typically
	// are NOT any null characters/bytes---but they can be common in
	// binary file formats!
	char bytes[100];
	fgets(bytes, 100, fp);
	printf("length of string read by fgets() is %lu bytes. String is: %s\n", strlen(bytes), bytes);
	// In the case above, fgets read all characters up until '\n', but
	// when printf() treats the file as a string, is stops printing
	// characters at the null character.


	// Calling fgets again will get the bytes after the '\n':
	fgets(bytes, 100, fp);
	printf("length of string read by fgets() is %lu bytes. String is: %s\n", strlen(bytes), bytes);
	fclose(fp);

	// delete output file.
	//unlink(FILENAME);

	return EXIT_SUCCESS;
}
