// Scott Kuhl
#define _POSIX_C_SOURCE 200112L
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	/* readlink() gives you the path that a symbolic link points
	 to. In this example, we get the path of the special link
	 /proc/self/exe which is always a symbolic link to the
	 executable on Linux machines.

	 For more information, see:
	 http://stackoverflow.com/questions/933850
	*/
	char buf[1024];
	ssize_t len = readlink("/proc/self/exe", buf, 1023);
	// readlink() does not null terminate the string. So, we make sure
	// that readlink won't completely fill the buffer and then also
	// set the byte after the last byte written to null.
	buf[len]='\0';
	printf("The path to this program is: %s\n", buf);
}
