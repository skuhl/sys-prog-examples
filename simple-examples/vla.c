// Scott Kuhl
#include <stdio.h>

void fixedArray()
{
	// This array has a length that is known by the compiler at
	// compile time.
	char fixedArray[6] = "hello";
	printf("%s\n", fixedArray);
}

/* Variable length arrays are supported by C99. As of 2015, they are
   not supported by Microsoft Visual Studio's compiler. Support for
   VLAs is *optional* in the newer C11 standard. You can make the
   compiler warn you about VLAs with the '-Wvla' compiler flag.

   One problem with VLAs is that if the array is too big, the behavior
   of your program may be undefined. For example, gcc allocates memory
   for VLAs on the stack---and allocating too much can overflow the
   stack. Setting a variable length array to a length of 0 or a
   negative number may also be undefined. For more information, see:
   https://www.securecoding.cert.org/confluence/display/c/ARR32-C.+Ensure+size+arguments+for+variable+length+arrays+are+in+a+valid+range

   Use malloc() to allocate large amounts of memory. The return value
   will tell you if it succeed or not (instead of a VLA which might
   crash your program if it fails).
   
*/
void variableLengthArray(int n)
{
	char vla[n]; // the compiler doesn't know how long VLA is until
				 // run-time. Therefore, this is a variable length
				 // array (VLA).
	
	for(int i=0; i<n; i++)
		vla[i]='X';
	vla[n-1] = '\0';
	printf("%s\n", vla);
}



int main(void)
{
	fixedArray();
	variableLengthArray(10);
}
