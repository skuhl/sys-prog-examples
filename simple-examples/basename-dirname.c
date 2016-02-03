// Scott Kuhl

/* This example demonstrates using dirname() and basename(). These
   functions allow you to split up a filename or path into a directory
   name and a filename.

   dirname() and basename() don't actually look for the files. These
   functions can be run on files that don't exist! These functions
   just look at the filename iteself and use the last part of the path as the
   basename and the beginning part of the path as the dirname.

   It is guaranteed that concatenating the dirname + "/" + basename
   will result in a path to the file.
*/

#define _GNU_SOURCE
#include <string.h> // needed for strdup()
/* NOTE: There is also a version of basename() provided by glibc
   available inside of string.h. If we didn't include libgen.h and
   only included string.h with _GNU_SOURCE defined, we would be using
   the glibc version of basename()---and it might be slightly
   different than the behavior of the POSIX basename() provided by libgen.h.

   One difference between the glibc and POSIX basename functions: If
   the filename has a trailing slash, the glibc version of basename()
   returns an empty string.
 */


#include <libgen.h>  /* necessary for POSIX basename() and dirname()
                        functions. If we include this header, POSIX
                        basename() is what we will actually use
                        instead of the one that may be available by
                        glibc in string.h */


#include <stdio.h>
#include <stdlib.h>


void dirname_basename(char *filename)
{

	/* dirname() and basename() may modify the strings that we pass to
	   it and return the new modified string. They may also return a
	   pointer to special section of memory that could be reused for a
	   subsequent call to the dirname() or basename() functions.

	   In either case...
	   
	   1) Do not free() the returned values.
	   
	   2) Do not assume that they will leave your original string
	   unchanged.
	   
	   3) Assume that the information that the returned point points
	   to may be changed by a subsequent dirname() or basename() call.
	*/

	printf("     original: %s\n", filename);
	
	// strdup() makes a copy of a null-terminated string, we should
	// free() the result.
	char *copyForDir = strdup(filename); // don't forget to free()
	char *dir = dirname(copyForDir);
	printf("      dirname: %s\n", dir);


	char *copyForBase = strdup(filename); // don't forget to free()
	char *base = basename(copyForBase);
	printf("     basename: %s\n", base);

	printf("reconstructed: %s/%s\n", dir, base);
	free(copyForDir);
	free(copyForBase);

	printf("\n");
}


int main(void)
{
	dirname_basename("/home/scully/xfile.txt");
	dirname_basename("test.txt");
	dirname_basename("/home/scully");
	dirname_basename("/home/");
	dirname_basename("///home/");
	dirname_basename("///home/");
	dirname_basename("//./home/");

	dirname_basename("/home");

	
	// Some special cases
	dirname_basename("/");
	dirname_basename(".");
	dirname_basename("..");

	// Try some other odd things...
	dirname_basename("./././");
	dirname_basename(".././");
	
	printf("Reconstructed version versions are: dirname + '/' + basename\n");
	printf("The reconstructed version should be functionally equivalent to the original filename (although the actual path may be different.)");
	
}
