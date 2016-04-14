// Scott Kuhl

/* execl() execlp() etc. are POSIX functions which *replace* the
   caller with a different program. I.e., you can make your program
   become a different program! These functions only return if an error
   occurs.

   The letters after exec in the function name mean:

   l - You can pass parameters to the function. In this case, you can
   pass a variable number of parameters depending on how many
   parameters the program needs. You must include NULL after your last
   parameter.

   v - The arguments will be passed to the exec() function using an
   array.
   
   p - The PATH environment variable is consulted when looking for the
   program.

   e - Allows you to specify environment variables that your program
   should be run with.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // necessary for exec*() functions.


int main(void)
{
	const int version = 4; // change me!

	if(version == 0)
	{
		/* First parameter is a program, the remaining parameters are
		 * passed to that program. Since PATH environment variable is
		 * not consulted, you must provide an absolute path or a path
		 * relative to the current directory that you are in. Last
		 * parameter must be a null pointer so exec() knows it hit the
		 * last one.
		 *
		 * Note that the first parameter IS the program that we want
		 * to execute. The second parameter is what will appear in
		 * argv[0] which is also typically the program name!
		 */
		execl("./argv-argc", "./argv-argc", "hello", "world", "testing a space!", NULL);
	}
	else if(version == 1)
	{
		/* execlp() is same as execl(), but PATH environment variable
		 * is consulted when it looks for the program. */
		execlp("ls", "ls", "-l", NULL);
	}
	else if(version == 2)
	{
		/* execle() is same as execl() but it also allows you to pass
		 * environment variables.
		 */
		char *envp[] = { "HOME=/home/no.such.user",
		                 NULL };
		
		// Note "ls ~" means list your home directory, but we have
		// changed the meaning of the home directory by changing the
		// environment variable.
		execle("/bin/ls", "ls", "~", NULL, envp);
	}
	else if(version == 3)
	{
		/* Same as execl(), but parameters are specified in an
		 * array. */
		char *argv[] = { "ls", 
		                 "-l",
		                 "-a",
		                 NULL };
		execv("/bin/ls", argv);
	}
	/* Other functions not demonstrated:
	   
	   execvp() - same as execv() except PATH is consulted.

	   execvpe() - same as execvp() except you can provide environment
	   variables.
	*/


	else if(version == 4)
	{
		/* All of the exec functions described are basically wrappers
		 * around execve(). */
		char *argv[] = {"ls", "-l", NULL};
		char *envp[] = { NULL }; // could set environment variables here. Keep NULL as last entry!
		execve("/bin/ls", argv, envp);
	}
	
	
	else
	{
		printf("You selected an invalid parameter.\n");
		exit(EXIT_FAILURE);
	}

	/* We can only get here if the exec*() function failed.
	   
	   Upon error, exec*() functions set errno. */
	perror("exec-related problem");


	printf("exec functions only return if there is an error. Therefore, this message is unlikely to be displayed.\n");

	exit(EXIT_FAILURE);
		
	
}
