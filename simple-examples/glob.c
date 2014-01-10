// Scott Kuhl
#include <unistd.h>
#include <stdio.h>
#include <glob.h>


int main(void)
{
	// Prints all .c files and all files beginning with "Mak" to the
	// console. Your shell uses glob() (or something similar) to allow
	// you to type "rm *"---and the shell expands the * to a list of
	// files before it actually runs the "rm" command.
	glob_t globbuf;
	glob("*.c", GLOB_ERR, NULL, &globbuf);
	glob("Mak*", GLOB_ERR | GLOB_APPEND, NULL, &globbuf);
	printf("glob pathc: %zu\n", globbuf.gl_pathc);
	for(unsigned int i=0; i<globbuf.gl_pathc; i++)
		printf("%s\n", globbuf.gl_pathv[i]);
	globfree(&globbuf);
}
