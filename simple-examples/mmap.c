// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>


#define FILENAME "mmap.temp"

void createFile(char *string)
{
	FILE *fp = fopen(FILENAME, "w");
	fprintf(fp, "%s", string);
	fclose(fp);
}

void printFile()
{
	FILE *fp = fopen(FILENAME, "r");
	char buf[100];
	fgets(buf, 100, fp);
	printf("file actually contains contains: %s\n", buf);
	fclose(fp);
}


// File-backed, private example---read from file
void readExample()
{
	createFile("hello world");

	int fd = open(FILENAME, O_RDONLY);
	size_t mmapLen = 15;
	off_t offset = 0; // offset to seek to.

	// We use MAP_PRIVATE since writes to the region of memory should
	// not be written back to the file.
	char *ptr = (char*) mmap(NULL, mmapLen,
	                         PROT_READ, MAP_PRIVATE,
	                         fd, offset);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	// File isn't necessarily loaded into memory until we access the
	// memory (causing a page fault to occur and making the kernel
	// handle it).
	
	printf("Should say hello world: %s\n", ptr);
	// I don't think mmap() makes any guarantees to what bytes are
	// past the end of the mmap(). But, on my machine they are
	// initialized to zero.
	for(unsigned int i=0; i<mmapLen; i++)
		printf("ptr[%u] is: '%c' (or %d)\n", i, ptr[i], ptr[i]);
	if(munmap(ptr, mmapLen) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
	
	close(fd);
}

// File-backed, private example---can write to mmapped memory, but won't be saved to file.
void readExampleChange()
{
	createFile("hello world");

	int fd = open(FILENAME, O_RDONLY);
	size_t mmapLen = 15;
	off_t offset = 0; // offset to seek to.
	char *ptr = (char*) mmap(NULL, mmapLen,
	                         PROT_READ|PROT_WRITE, MAP_PRIVATE,
	                         fd, offset);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	printf("Should say hello world: %s\n", ptr);

	// In this case (MAP_PRIVATE), writing to the area of memory will
	// be allowed, but our changes aren't saved to the file itself.
	ptr[0] = 'J';
	printf("Should say Jello world: %s\n", ptr);

	/* It is unspecified whether changes made to the file after the
	 * mmap() call are visible in the mapped region. */
	createFile("hello WORLD");
	printf("Undefined. Might say hello WORLD: %s\n", ptr);
	
	if(munmap(ptr, mmapLen) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
	
	close(fd);
}



// File-backed, shared example---write to file.
void writeExample()
{
	createFile("hello world");

	int fd = open(FILENAME, O_RDWR);
	size_t mmapLen = 15;
	off_t offset = 0; // offset to seek to.

	// We use MAP_SHARED to write changes back to file.
	char *ptr = (char*) mmap(NULL, mmapLen,
	                         PROT_READ|PROT_WRITE, MAP_SHARED,
	                         fd, offset);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	printf("Before we change the file. Should say hello world: %s\n", ptr);
	ptr[0] = 'J';
	printf("After we change the mmap'd memory. Should say hello world: %s\n", ptr);
	printf("File after we change mmap'd memory is undefined before we call msync():\n");
	printFile();
	msync(ptr, mmapLen, MS_SYNC);
	printf("File after we change mmap'd memory contains all changes after we call msync():\n");
	printFile();
	
	if(munmap(ptr, mmapLen) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

// anonymous, private example
void mmapAlloc()
{
	// mmap can be used to allocate memory---just like malloc().  If
	// MAP_ANONYMOUS isn't available, you can try mapping the special
	// file /dev/zero.
	size_t mmapLen = 8;
	char *ptr = (char*) mmap(NULL, mmapLen,
	                         PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE,
	                         -1, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	// ptr can be used just like malloc (note: using malloc() is
	// easier than allocating memory this way!)

	if(munmap(ptr, mmapLen) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}

}

// anonymous private example
void mmapAnonPrivate()
{
	// We use MAP_ANONYMOUS to create a section of memory that we can
	// use, but isn't associated with a file.
	size_t mmapLen = 8;
	char *ptr = (char*) mmap(NULL, mmapLen,
	                         PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE,
	                         -1, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	printf("memory is initialized to zero with MAP_ANONYMOUS\n");
	for(unsigned int i=0; i<mmapLen; i++)
		printf("ptr[%u] = %d\n", i, ptr[i]);

	if(fork() == 0)
	{
		// If we are the child, print out the data.
		for(unsigned int i=0; i<mmapLen; i++)
			printf("child: ptr[%u] = %d\n", i, ptr[i]);
#if 0
		// child won't ever see the changes the parent makes:
		printf("Child is waiting.\n");
		while(ptr[mmapLen-1] == 0); // wait for parent to change values
		printf("Child is done waiting.\n");
		for(unsigned int i=0; i<mmapLen; i++)
			printf("child ptr[%u] = %d\n", i, ptr[i]);
#endif
		printf("Child exited\n");
		exit(EXIT_SUCCESS);
	}

	printf("Parent is writing data to the mmap'd area\n");
	for(unsigned int i=0; i<mmapLen; i++)
		ptr[i] = i;
	printf("Parent is done writing data to the mmap'd area\n");

	printf("Parent is waiting for the child to finish\n");
	wait(NULL); // wait for child to finish.
	printf("Parent detected that child exited.\n");
	
	printf("Contents after we store values in memory.\n");
	for(unsigned int i=0; i<mmapLen; i++)
		printf("ptr[%u] = %d\n", i, ptr[i]);

	if(munmap(ptr, mmapLen) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
}

// anonymous, shared example
void mmapAnonShared()
{
	// We use MAP_ANONYMOUS to create a section of memory that we can
	// use, but isn't associated with a file.
	size_t mmapLen = 8;
	char *ptr = (char*) mmap(NULL, mmapLen,
	                         PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED,
	                         -1, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	printf("memory is initialized to zero with MAP_ANONYMOUS\n");
	for(unsigned int i=0; i<mmapLen; i++)
		printf("ptr[%u] = %d\n", i, ptr[i]);

	// We should check to see if fork() returns -1 to indicate an
	// error occurred.
	if(fork() == 0)
	{
		// The parent and child processes are now sharing the same piece of memory.
		for(unsigned int i=0; i<mmapLen; i++)
			printf("child: ptr[%u] = %d\n", i, ptr[i]);
		printf("Child is putting non-zero data at the beginning of the mma'd area\n");
		ptr[0] = 42; // indicate to parent that we printed stuff out.

		printf("Child is waiting for non-zero data at the end of the mmap'd area...\n");
		while(ptr[mmapLen-1] == 0); // wait for parent to change values
		printf("Child is done waiting.\n");
		for(unsigned int i=0; i<mmapLen; i++)
			printf("child ptr[%u] = %d\n", i, ptr[i]);
		printf("Child exited.\n");
		exit(EXIT_SUCCESS);
	}

	printf("Parent is waiting for non-zero data in the beginning of the mmap'd area.\n");
	while(ptr[0] == 0); // wait for child to print out stuff.
	printf("Parent is done waiting, writing data into entire mmap'd area...\n");
	for(unsigned int i=0; i<mmapLen; i++)
		ptr[i] = i;
	printf("Parent is done writing data\n");

	printf("Parent is waiting for the child to finish\n");
	wait(NULL); // wait for child to finish.
	printf("Parent detected that child exited.\n");
	
	printf("Contents after we store values in memory.\n");
	for(unsigned int i=0; i<mmapLen; i++)
		printf("ptr[%u] = %d\n", i, ptr[i]);

	if(munmap(ptr, mmapLen) == -1)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
}



int main(void)
{
	printf("================= SUMMARY OF MMAP() OPTIONS ===================\n");
	printf("        | File-backed (default)      | Anonymous               \n");
	printf("--------+----------------------------+-------------------------\n");
	printf("Private:| Init memory based on file. | Like malloc(), init to 0\n");
	printf("--------+----------------------------+-------------------------\n");
	printf("Shared: | Init memory based on file. | Share memory between    \n");
	printf("        | Write to file when done.   | processes. Init to 0.   \n");
	printf("        | Shared between processes.  |                         \n");

	printf("\n\n--- readExample() ---\n");
	readExample();
	printf("\n\n--- readExampleChange() ---\n");
	readExampleChange();

	printf("\n\n--- writeExample() ---\n");
	writeExample();

	printf("\n\n--- mmapAlloc() ---\n");
	mmapAlloc();
	
	printf("\n\n--- mmapAnonPrivate() ---\n");
	mmapAnonPrivate();
	
	printf("\n\n--- mmapAnonShared() ---\n");
	mmapAnonShared();

}
