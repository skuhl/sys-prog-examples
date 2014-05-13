// Scott Kuhl

/* The stat() method allows you get information about a file. This
   example demonstrates some of the information that stat() can
   provide. For more information, run "man 2 stat". Most systems have
   a program called "stat" that you can run at the command line to see
   information about the file. Therefore, make sure that you run this
   program with "./stat" to ensure that you are running this program
   and not the stat executable typically installed in /usr/bin/ (or
   some other common path).
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	(void)argc; // hide compiler warning about unused variable
	char *file = argv[0];
	printf("Looking at: %s\n", file);
	
	/* Lets stat() this executable! */
	struct stat fileStat; // allocate space on stack to store the result.
	if(stat(file, &fileStat) < 0)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}

	printf("File size: %zu bytes\n", fileStat.st_size);
	printf("Owner user ID: %d\n", fileStat.st_uid);
	printf("Owner group ID: %d\n", fileStat.st_gid);

	if(S_ISDIR(fileStat.st_mode))
		printf("It is a directory\n");
	if(S_ISLNK(fileStat.st_mode))
		printf("It is a symbolic link.\n");
	if(S_ISREG(fileStat.st_mode))
		printf("It is a regular file.\n");

	if(fileStat.st_mode & S_IROTH)
		printf("World has read permission.\n");
	if(fileStat.st_mode & S_IWOTH)
		printf("World has write permission.\n");
	if(fileStat.st_mode & S_IXOTH)
		printf("World has execute permission.\n");

	printf("NOTE: This program only prints some of the information about the file that stat() provides.\n");
	
	return EXIT_SUCCESS;
}
