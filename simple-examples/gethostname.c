// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char name[1024] = "";
	if(gethostname(name, 1024) != 0)
	{
		perror("gethostname");
		return 1;
	}
	printf("hostname is: %s\n", name);


	if(getdomainname(name, 1024) != 0)
	{
		perror("getdomainname");
		return 1;
	}
	printf("domain name is: %s\n", name);

	return 0;
}
