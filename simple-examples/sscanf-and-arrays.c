// Scott Kuhl
#include <stdio.h>

int main(void)
{
	char str[100] = "";
	// str is a pointer to the first element in the array
	// str[0] is the first element in the array
	int i = 0;

	// Parse a string into the str and i variables:
	sscanf("6 six", "%d %s", &i, &str); // MISTAKE: str is already a pointer!

	// Even with this mistake, it might still work!
	printf("Might be '6 six': %d %s\n", i, str);

	// Correct:
	sscanf("6 six", "%d %s", &i, str);
	printf("Will be '6 six': %d %s\n", i, str);

	return 0;
}
