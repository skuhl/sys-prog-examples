/* Scott Kuhl

 Compile with -rdynamic for function names in the backtrace. Also, the
 optimization settings that you compile with may influence the
 backtrace you see in this example.
*/
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void print_backtrace(void)
{
	void *buffer[1024];
	int count = backtrace(buffer, 1024);

	char **strings = backtrace_symbols(buffer, 1024);
	if(strings == NULL)
	{
		perror("backtrace_symboles");
		exit(EXIT_FAILURE);
	}
	printf("Backtrace:\n");
	for(int i=0; i<count; i++)
		printf("%s\n", (char*)strings[i]);
	free(strings);
}

void a(void)
{
	print_backtrace();
}

int main(void)
{
	a();
}

