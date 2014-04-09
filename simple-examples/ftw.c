// Scott Kuhl
//
// This example is simplified from the example in the man page. It
// recursively prints out all of the files in the current directory.
#define _GNU_SOURCE
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int display_info(const char *fpath, const struct stat *sb,
                        int tflag, struct FTW *ftwbuf)
{
	char *type = "other";
	if(tflag == FTW_F)
		type = "file ";
	else if(tflag == FTW_D)
		type = "dir  ";
	
	printf("type=%s level=%02d, size=%07ld path=%s filename=%s\n",
	       type, ftwbuf->level, (intmax_t) sb->st_size,
	       fpath, fpath + ftwbuf->base);

	return 0;  // continue
}

int main(void)
{
	if(nftw(".", display_info, 20, 0) == -1)
	{
		perror("nftw");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
