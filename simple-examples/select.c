// Scott Kuhl
//
// select() lets you wait for up to a certain amount of time for a
// file descriptor to become ready for some kind of IO. It is similar
// to poll().
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	// select() uses an array of bits (in datatype fd_set)---and each
	// bit corresponds to a file descriptor. We set the bits that
	// correspond to the file descriptors we want to watch. FD_SETSIZE
	// indicates the number of bits in in fd_set. We can't watch a
	// file descriptor that is >= FD_SETSIZE. See poll() for an
	// alternative!
	printf("FD_SETSIZE=%d\n", FD_SETSIZE);
	printf("Wait 5 seconds for select() to time out, or press a key to cause it to return before it times out.\n");
	
	fd_set rfds;
	FD_ZERO(&rfds); // clear bit array.
	FD_SET(STDIN_FILENO, &rfds); // set bit for stdin=0
	// Other functions:
	// FD_ISSET(int fd, fd_set *set) -- is a bit set?
	// FD_CLR(int fd, fd_set *set) -- clears a bit
	
	// select() will block for up to 5 seconds
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0; // microseconds

	// The first parameter to select() is nfds: The ONE PLUS the
	// number of the highest file descriptor that might be set in
	// rfds.
	//
	// select() will wait until a timeout occurs. Note that if we are
	// waiting on more than one file descriptor (i.e., there is more
	// than one bit enabled in the set), then select() will return
	// when one or more of them is ready. In this example, we are only
	// waiting on one fd.
	
	int retval = select(STDIN_FILENO+1, &rfds, NULL, NULL, &tv);
	// select() may have changed the value of tv. Linux sets it to the
	// remaining time that wasn't slept. Many other implementations do
	// not do this. The POSIX standard permits either behavior.

	if (retval == -1)
		perror("select()");
	else if (retval)
		printf("There is data to read from the file descriptor (%d of the fds are ready).\n", retval);
	else
		printf("We timed out waiting for there to be data to read from the file descriptor.\n");


	/* Try to read the bytes from stdin using read(). If we don't do
	 * this, the message that the user typed might instead get sent to
	 * the shell!
	 */
	if(1) // TRY THIS: Change this to 0!
	{
		char buf[1024];
		read(STDIN_FILENO, buf, 1024);
	}

	exit(EXIT_SUCCESS);
}
