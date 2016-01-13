// Scott Kuhl

#include <stdio.h>

#ifdef __linux__

#include <sys/sysinfo.h>
int main(void)
{
	printf("get_nprocs_conf() returns %d\n", get_nprocs_conf());
	printf("get_nprocs() returns %d\n", get_nprocs());
	return 0;
}


#else

int main(void)
{
	printf("This example only works on Linux\n");
	return 0;
}

#endif
