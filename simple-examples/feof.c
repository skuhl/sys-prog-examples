// Scott Kuhl
#include <stdio.h>

#define FILENAME "feof.temp"

int main(void)
{
	// NOTE: We should check return values for errors.

	// Write 8 bytes to file.
	FILE *out = fopen(FILENAME, "w");
	char bytes[] = { 1,2,3,4,5,6,7,8 };
	fwrite(bytes, sizeof(char), 8, out);
	fclose(out);

	for(int i=0; i<8; i++)
		bytes[i] = 0;

	// Read the 8 bytes
	FILE *in = fopen(FILENAME, "r");
	fread(bytes, sizeof(char), 8, in);

	/* feof() checks if the end-of-file indicator is set for this
	   stream. It is only set if you try to read *past* the end of the
	   file. Once you read past the end of the file, you can use
	   feof() or ferror() to figure out if an error occurred or if you
	   hit the end of the file.
	*/

	/* Here we are really at the end of the file, but we haven't tried
	   reading past it yet. */
	if(feof(in) == 0)
		printf("First feof() says that we are NOT at the end of the file.\n");
	else
		printf("First feof() says that we ARE at the end of the file.\n");

	/* Read one byte past the end of the file */
	char b;
	if(fread(&b, 1,1, in) == 0)
	{
		if(feof(in) == 0)
			printf("Second feof() says that we are NOT at the end of the file.\n");
		else
			printf("Second feof() says that we ARE at the end of the file.\n");

		if(ferror(in) == 0)
			printf("ferror() says there are NO errors.\n");
		else
			printf("ferror() says there ARE errors.\n");

	}
	else
	{
		printf("This should never happen. The file should only contain 8 bytes and the fread() above should always fail.\n");
	}

	fclose(in);
	return 0;
}
