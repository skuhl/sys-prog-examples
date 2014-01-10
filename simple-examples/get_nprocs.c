// Scott Kuhl
#include <stdio.h>
#include <sys/sysinfo.h>


int main(void)
{
	printf("get_nprocs_conf() returns %d\n", get_nprocs_conf());
	printf("get_nprocs() returns %d\n", get_nprocs());
	return 0;
}
