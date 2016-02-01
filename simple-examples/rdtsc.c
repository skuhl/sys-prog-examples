// Scott Kuhl

/*
 ReaD Time Stamp Counter (RDTSC) instruction. Returns number of
 clock cycles since boot. Should work on recent 64 bit machines.

 A more thorough discussion can be found in "How to Benchmark Code
 Execution Times on Intel IA-32 and IA-64 Instruction Set
 Architectures" by Gabriele Paoloni (Intel):
http://www.intel.com/content/www/xr/en/intelligent-systems/embedded-systems-training/ia-32-ia-64-benchmark-code-execution-paper.html

Compiled program can be inspected with "objdump -d rdtsc"
 
 POTENTIAL PROBLEMS:

 - Frequency changes: Some processors change frequencies depending on
   load for power-saving reasons. Usually this can be prevented with a
   setting on your OS. "cat /proc/cpuinfo" can tell you the current
   frequency of your processor.

 - Cache: If there is a cache miss, your code will take more cycles to
   execute. Running your test multiple times may help.

 - Out of order instructions: The cpuid instruction can force all
   previous instructions to finish.

 - Context switches: The counter will increase when other processes
   are switched in. Problem can be minimized by reducing number of
   instructions between start/stop or by setting the process priority
   to the highest possible priority.

 - Multi-core processors: The counters aren't synchronized across
   cores. If your process switches cores, your values may not make
   sense. The process affinity can be to prevent process migration
   between cores/processors.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>


// Use the preprocessor so we know definitively that these are placed inline
#define RDTSC_START()            \
	__asm__ volatile("CPUID\n\t" \
	                 "RDTSC\n\t" \
	                 "mov %%edx, %0\n\t" \
	                 "mov %%eax, %1\n\t" \
	                 : "=r" (start_hi), "=r" (start_lo) \
	                 :: "%rax", "%rbx", "%rcx", "%rdx");

#define RDTSC_STOP()              \
	__asm__ volatile("RDTSCP\n\t" \
	                 "mov %%edx, %0\n\t" \
	                 "mov %%eax, %1\n\t" \
	                 "CPUID\n\t" \
	                 : "=r" (end_hi), "=r" (end_lo) \
	                 :: "%rax", "%rbx", "%rcx", "%rdx");

// Returns the elapsed time given the high and low bits of the start and stop time.
uint64_t elapsed(uint32_t start_hi, uint32_t start_lo,
                 uint32_t end_hi,   uint32_t end_lo)
{
	uint64_t start = (((uint64_t)start_hi) << 32) | start_lo;
	uint64_t end   = (((uint64_t)end_hi)   << 32) | end_lo;
	return end-start;
}

int main(void)
{
	uint32_t start_hi=0, start_lo=0; 
	uint32_t   end_hi=0,   end_lo=0;

	RDTSC_START();
	sleep(1);
	RDTSC_STOP();
	printf("elapsed: %ld (sleep(1))\n", elapsed(start_hi, start_lo, end_hi, end_lo));
	printf("\n\n\n");


	// For the rest of our tests, lets use loops to get more accurate numbers.

#define REPEAT 100
	
	uint64_t totalTime = 0;
	for(int i=0; i<REPEAT; i++)
	{
		RDTSC_START();
		printf("printing!\n"); // how fast is printf()?
		RDTSC_STOP();
		uint64_t e = elapsed(start_hi, start_lo, end_hi, end_lo);
		printf("trial %d: %ld (printf)\n", i, e);
		totalTime += e;
	}
	printf("average: %f\n", totalTime/(float)REPEAT);

	
	printf("\n\n\n");
	totalTime = 0;
	for(int i=0; i<REPEAT; i++)
	{
		RDTSC_START();
		// how fast is nothing at all?
		RDTSC_STOP();
		uint64_t e = elapsed(start_hi, start_lo, end_hi, end_lo);
		printf("trial %d: %ld (NOTHING)\n", i, e);
		totalTime += e;
	}
	printf("average: %f\n", totalTime/(float)REPEAT);
	printf("\n\n\n");

	totalTime = 0;
	for(int i=0; i<REPEAT; i++)
	{
		volatile int var = 0;
		int k=0; 
		RDTSC_START();
		// how fast is a loop that we can choose how many times it runs?
		for(; k<2; k++) // Change how many times this loop runs, see what happens.
			(var) = 1;
		RDTSC_STOP();
		uint64_t e = elapsed(start_hi, start_lo, end_hi, end_lo);
		printf("trial %d: %ld (loop)\n", i, e);
		totalTime += e;
	}
	printf("average: %f\n", totalTime/(float)REPEAT);


	return 0;
}
