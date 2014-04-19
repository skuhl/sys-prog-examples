// Scott Kuhl
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(void)
{
	// A struct allows you to consolidate multiple variables into a
	// single variable.
	typedef struct {
		int a;
		int b;
	} pair;

	// There are several ways to create a new variable from a struct
	pair x = {    1,    2 };
	pair y = { .a=1, .b=2 };
	pair z;
	z.a = 1; // dot allows you to access an element in a struct
	z.b = 2;

	pair *m = malloc(sizeof(pair));
	// -> arrow allows you to access an element from a pointer to a struct.
	m->a = 10; 
	m->b = 20;

	// print out all of the values of a (to hide compiler warnings!)
	printf("%d %d %d %d\n", x.a, y.a, z.a, m->a);

	free(m);
	return 0;
}
