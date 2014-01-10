// Scott Kuhl
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	printf("rand() will return values from 0 up through %d\n", RAND_MAX);
	for(int i=0; i<5; i++)
		printf("%d\n", rand());
}
