// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

int main(void)
{
	struct utsname buf;
	if(uname(&buf) != 0)
	{
		perror("uname");
		return 1;
	}
	printf("sysname:    %s\n", buf.sysname);
	printf("nodename:   %s\n", buf.nodename);
	printf("release:    %s\n", buf.release);
	printf("version:    %s\n", buf.version);
	printf("machine:    %s\n", buf.machine);
	printf("domainname: %s\n", buf.domainname);
}
