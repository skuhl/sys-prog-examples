#include <stdio.h>

#include "head.h"
#include "subdir/subfile.h"


int main()
{
  subfile();
  printf("hello world\n");
  return 0;
}
