// Scott Kuhl
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	long ticks = sysconf(_SC_CLK_TCK);
	printf("Ticks: %ld\n", ticks);
}

