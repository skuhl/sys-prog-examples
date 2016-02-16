// Scott Kuhl

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h> // strerror()

#define NUMTHREADS 10 // TRY THIS: Make this number larger.

pthread_t threads[NUMTHREADS];
pthread_mutex_t lock;
int counter;

void* doSomething(void *ptr)
{
	int i = *((int*)ptr);

	// Note: Multiple threads may report that they are the same
	// number. The reason is that we passed in the same pointer to the
	// 'i' variable when we created the threads. Therefore, depending
	// on if this thread runs while the for loop is running, we might
	// get different behavior. The best way to fix this problem is to
	// use a separate pice of memory for the argument for each thread.
	printf("This is %d\n", i);  

	pthread_mutex_lock(&lock); // acquire lock
	printf("Counter was at %d\n", counter);
	counter += 1;
	sleep(1);
	printf("Counter is now at %d\n", counter);

	pthread_mutex_unlock(&lock);

	// Alternative to return: We could call pthread_exit() to exit this thread.
	return NULL;
}

int main(void)
{
	// initialize a mutex lock
	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Unable to initialize mutex\n");
		return 1;
	}

	counter = 0;

	for(int i=0; i<NUMTHREADS; i++)
	{
		// make thread call doSomething(), we can pass one argument as
		// a void* (in this case, a pointer to i)
		int err = pthread_create(&(threads[i]), NULL, &doSomething, &i);

		if(err != 0)
			printf("Failed to create thread %d due to error: %s\n", i, strerror(err));
	}

	// Wait for each thread to exit
	for(int i=0; i<NUMTHREADS; i++)
	{
		printf("Waiting for thread %d\n", i);

		// The second argument can be used to retrieve the void* that the thread returns.
		pthread_join(threads[i], NULL);
	}

	printf("Finishing. Destroying mutex...\n");
	pthread_mutex_destroy(&lock);

	return 0;
}
	
