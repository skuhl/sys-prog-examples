// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

// Set this to 0 to try the same program with locking disabled.
#define USE_LOCK 1

#define FILENAME "fcntl-lock.temp"

int main(void)
{
	unlink(FILENAME);
	int child = fork();
	char buf[1024];
	if(child == 0)
		strcpy(buf, "aaa aaa aaa aaa\n");
	else
		strcpy(buf, "bbb bbb bbb bbb\n");

	
	int sharedFd = open(FILENAME, O_RDWR|O_APPEND|O_CREAT, 0600);

	for(int j=0; j<1000; j++)
	{

#if USE_LOCK==1
		// Note: these locks are advisory, and require other processes
		// using the file to explicitly check for a lock before using
		// the file.
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;  // lock all bytes from here to end of file
		fcntl(sharedFd, F_SETLKW, &lock);   // will block until we can set our lock
#endif
		
		// write the string to the file one character at a time.
		for(int i=0; i<(int)strlen(buf); i++)
			write(sharedFd, &(buf[i]), 1);

#if USE_LOCK==1
		lock.l_type = F_UNLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;
		fcntl(sharedFd, F_SETLK, &lock);

		// sleep for 1/1000th of a second to increase likelihood that
		// the other process will have an opportunity to print
		// something to the file. Without this, some machines
		// basically have one process write everything out and then
		// the other process writes everything out.
		struct timespec slptm;
		slptm.tv_sec = 0;
		slptm.tv_nsec = 1000000000/1000;
		nanosleep(&slptm, NULL);
#endif
	}


	if(child > 0)
	{
#if USE_LOCK==1
		wait(NULL);
#endif
		printf("Look in %s\n", FILENAME);
	}
	return 0;
}
