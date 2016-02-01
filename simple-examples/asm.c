// Scott Kuhl

/* Demonstrates how to use assembly instructions in C code */

#include <stdio.h>

int var1, var2;

void reset_operands(void)
{
	var1 = 333;
	var2 = 123;
}

int main(void)
{

	
	/* Add 1 to var1 and store the result in var1. */
	reset_operands();
	printf("%d + 1 = ", var1); 
	__asm__ volatile ("add $1, %0\r\n" // add instruction. '%' means register name, '$' means a literal value
	                  /* Operands follow (first one is %0, second one is %1, etc): */
	                  
	                  // output operands:
	                  :"=r" (var1)    // '=' means write-only; 'r' means general purpose register
	                   
	                   // input operands:
	                  :"0" (var1)     // '0' = means this operand must occupy the same location as output operand 0

	                   // clobbered registers
	                  : // none!
		);
	printf("%d\n",  var1); // result


	/* Add var1 and var2, store result in operand 1 */
	reset_operands();
	printf("%d + %d = ", var1, var2);
	__asm__ volatile ("add %2, %0\r\n" // add two registers
	                  
	                  // output operands:
	                  :"=r" (var1)
	                   
	                   // input operands:
	                  :"0" (var1), "r" (var2)

	                   // clobbered registers
	                  : // none!
		);
	printf("%d\n", var1);



	/* Swap var1 and var2. */
	reset_operands();
	printf("var1=%d, var2=%d\n", var1, var2);
	__asm__ volatile ("mov %0, %%eax;\n"   // copy operand 0 into the eax register
	                  "mov %1, %0;\n"      // overwrite operand 0 with the contents of operand1.
	                  "mov %%eax, %1;\n"   // move data from eax into operand 1

	                  // output operands:
	                  :"=r" (var1), "=r" (var2)
	                   
	                   // input operands:
	                  :"0" (var1), "1" (var2)

	                   // Clobbered operands (we used %eax as a temporary storage location)
	                  : "%eax"
		);
	printf("var1=%d, var2=%d\n", var1, var2);
}
