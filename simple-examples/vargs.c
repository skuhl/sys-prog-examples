// Scott Kuhl

/* This example demonstrates how to create C functions that accept a
   variable number of argList.
 
   One important note: C does not provide a way for you to determine
   how many argList a caller actually used when they called a method
   that accepts a variable number of argList. Therefore, the
   function must be able to look at the argList and deduce the
   number of argList that the caller used. There are at least two
   commonly used methods to accomplish this task:

     1) Force the caller to set the last argument to some special value (a NULL pointer, 0, etc.). Demonstrated in sum_end0().

     2) Force the caller to indicate the number of argList in the
     first argument (or one of the other argList that the function
     requires). This concept is demonstrated in sum_count().
 
   In the examples below, all argList are the same type. This
   doesn't necessarily have to be the case!

 */
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>


/* Sums a list of integers. The last integer must be a zero. */
int sum_end0(int values, ...)
{
	printf("Running: sum_end(..., 0)\n");

	/* Initialize argList. */
	va_list argList;
	va_start(argList, values);

	/* Calculate sum until we reach a 0 argument. */
	int thisNum = values;
	int sum = 0;
	while(thisNum != 0)
	{
		printf("arg=%d\n", thisNum);
		sum = sum+thisNum; /* BUG: We aren't checking for overflow! */
		thisNum = va_arg(argList, int);
	} while(thisNum != 0);
	printf("arg=%d <- found the zero!\n", thisNum);

	printf("sum_end0(..., 0) is returning: %d\n\n", sum);
	return sum;
}

/* Sums a list of integers. The first integer must be the number of
 * integers that follow it. */
int sum_count(int args, ...)
{
	printf("Running: sum_count(count, ...)\n");

	/* Initialize argList. */
	va_list argList;
	va_start(argList, args);

	/* Get the number of argList stored in the first argument. */
	int count = args;
	printf("Caller indicated that there are %d argument(s).\n", count);

	/* Calculate the sum */
	int sum=0;
	for(int i=0; i<count; i++)
	{
		int thisNum = va_arg(argList, int);
		printf("arg=%d\n", thisNum);
		sum = sum+thisNum;
	}

	printf("sum_count(count, ...) is returning: %d\n\n", sum);
	return sum;
	

}



int main(void)
{
	sum_end0(1,2,3,0);
	sum_count(3, 1,2,3);
	
	printf("-------------------\n");
	printf("Check some edge cases:");
	sum_end0(0);
	sum_end0(1,0);
	sum_count(0);
	sum_count(1, 1);



	printf("-------------------\n");
	/* All of the following are incorrect ways to use the example sum
	 * methods. Some of them may have undefined behavior and/or crash
	 * your program. */
//	sum_count(3, 1,2,3,4); // Shouldn't crash, but last value not summed
	
//	sum_count(3, 1,2);         // Might crash.
//	sum_count(100, 1,2,3);     // Might crash
//	sum_count(INT_MAX, 1,2,3); // Probably crash.

//	printf("-------------------\n");
//	printf("Use sum_end0() incorrectly:");

	/* Maybe crash, maybe return successfully if it
	   reaches something that looks like an 'int' set
	   to 0. */
//	sum_end0(1,2,3);  

	return 0;
}
