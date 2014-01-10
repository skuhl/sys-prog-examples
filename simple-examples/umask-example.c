// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "umask-example.temp"

void printFilePerms(void)
{
	FILE *poutput = popen("ls -l " FILENAME, "r");
	char buff[512];
	while(fgets(buff, sizeof(buff), poutput)!=NULL){
		printf("%s", buff);
	}
	pclose(poutput);
}

void createFile(mode_t mode)
{
	unlink(FILENAME); // delete the file if it exists.
	int fd = open(FILENAME, O_CREAT, mode); // create the file
	close(fd);
}

int main(void)
{
	// putting 0 before an integer causes the compiler to interpret it
	// as an octal value!
	printf("Decimal %d and octal %d\n\n", 777, 0777);


	// This example will do different things depending on what your
	// umask is set to when you run the program.
	printf("Trying to create a file with rwxrwxrwx permissions with open()\n");
	createFile(0777);
	printFilePerms();
	printf("\n");

	// Setting the umask to 0000 will allow any bits to be set in a
	// file created by open().
	printf("Setting umask to 0000\n");
	umask(0000); // there is also a command-line program named umask
				 // that allows you to change your umask. You can
				 // permanently set your umask in your ~/.bashrc or
				 // similar files that your shell runs when they
				 // start.
	printf("Trying to create a file with rwxrwxrwx permissions with open()\n");
	createFile(0777);
	printFilePerms();
	printf("\n");

	// the umask prohibits bits from being set when a file is created
	// with open(), but those bits don't necessarily all need to be
	// set. In this example, we set umask to 000---meaning that any
	// file we create could have any permissions set. But, those bits
	// aren't set unless we request that they get set.
	printf("Setting umask to 0000\n");
	umask(0000);
	printf("Trying to create a file with rwx------ permissions with open()\n");
	createFile(0700);
	printFilePerms();
	printf("\n");

	// Setting the umask to 077 is a good value if you only want
	// yourself to be able to read/write most of files that are
	// created.
	printf("Setting umask to 0077\n");
	umask(0077);
	printf("Trying to create a file with rwxrwxrwx permissions with open()\n");
	createFile(0777);
	printFilePerms();
	printf("\n");

	// Just because we allow the owners execute bit to be set, it
	// doesn't mean that every file that we create is going to have it
	// set:
	printf("Setting umask to 0077\n");
	umask(0077);
	printf("Trying to create a file with rw-rw-rw- permissions with open()\n");
	createFile(0666);
	printFilePerms();

	// Umasks are inherited from the parent process. If you type
	// "umask" on the command line to see your current umask after you
	// run this program, you will see that your umask of the parent
	// process (i.e., the shell) is NOT set to 321.
	umask(0321);

	unlink(FILENAME); // No need to keep the file after program exits...
	
	return 0;
}
