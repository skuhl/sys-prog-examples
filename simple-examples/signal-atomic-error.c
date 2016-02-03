/* This example is a modified form of:
   http://www.gnu.org/software/libc/manual/html_node/Non_002datomic-Example.html

   From the glibc manual. On some machines, it is possible for this
   program to print 0,1 or 1,0 since the signal handler may run
   in-between the full struct getting set to 0 or 1. This is why using
   sig_atomic_t for the datatype for the signal handler is important.
*/
#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
     
// The behavior of this program may change depending on if you change
// the type below from long to int.
volatile struct two_words { long a, b; } memory;
     
void handler(int signum)
{
	if(memory.a != memory.b)
		printf("MISMATCH!!!!\n");
	else
		printf("match\n");
}
     
int main (void)
{
        static struct two_words zeros = { 0, 0 }, ones = { 1, 1 };
        signal(SIGALRM, handler);
        memory = zeros;

        // send a new SIGALRM signal every 1000 microseconds
        ualarm(1, 1000);

        // It can take several instructions to do these
        // assignments. Therefore a signal could happen in the middle
        // of these assignments.
        while(1)
        {
                memory = zeros;
                memory = ones;
        }
}
