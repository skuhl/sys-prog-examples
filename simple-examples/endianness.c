// Scott Kuhl

/*
 When a data type uses multiple bytes (for example, a 32-bit int or a
 64-bit float), the order that the bytes are stored is dependent on
 the architecture of your machine.

 Little endian: Least significant byte first. Bytes (not the bits!)
 are put in the opposite order from what you might expect. Used by x86
 machines (i.e., most laptops, desktops)

 Big endian: Most significant byte first. Typically used to send
 information over the a network. Also used by some processors.

 Endianness is particularly important when information is shared
 between computers since they need to agree on the format that is
 used. For example, when you write information to a disk or
 communicate on a network.

 ASCII text files are made up of single-byte characters and therefore
 ASCII text files can be transferred between computers without concern
 about endianness.

 Unicode files may include multi-byte characters. By default, those
 multi-byte characters are in big-endian ordering. However, Unicode
 provides a Byte Order Mark (BOM) character which can be included in
 the Unicode file to indicate the endianness of the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <inttypes.h>


#define FILENAME "endianness.temp"
int main(void)
{
	// IMPORTANT NOTE: This program (and the corresponding comments)
	// make the most sense when run on a little endian machine!
	
	/* When I use the constant hexadecimal number "0xdeadbeef" in a
	   program, it will be stored as 0xefbeadde on a little-endian
	   machine. This conversion is mostly "hidden" from the view of
	   the programmer. */
	int32_t fourBytes = 0xdeadbeef;
	/* This will print out "deadbeef" since the compiler will convert
	   from the architecture-specific endianness back to big endian.
	   PRIx32 is a special way to print a int32_t type in
	   hexadecimal. See stdint.c for more info. */
	printf("Hex of the four bytes: %"PRIx32"\n", fourBytes);
	

	// Write the bytes to a file:
	FILE *fs = fopen(FILENAME, "w");
	printf("Writing 4 bytes, 1 byte at a time\n");
	fwrite(&fourBytes, 1, 4, fs); // fwrite() does not change the order of bytes.
	fclose(fs);
	printf("Note: If you are on a little-endian machine, this actually wrote: 0xefbeadde to the file! Run 'hexdump %s' or 'xxd %s' to convince yourself of that!\n", FILENAME, FILENAME);


	// Read the bytes back out of the file without changing any ordering.
	int32_t fromFile = 0;
	fs = fopen(FILENAME, "r");
	printf("Reading 4 bytes.\n");
	// This will read the bytes and put them in the int32_t object
	// without swapping anything.
	fread(&fromFile, 1, 4, fs);
//	fread(&fromFile, 4, 1, fs); // This won't affect the behavior of the program.
	fclose(fs);

	/* fromFile and fourBytes will be the same (i.e., they will both
	   be the same number in little endian format) */
	if(fromFile == fourBytes)
		printf("We read the same thing that we wrote.\n");
	else
		printf("We did NOT read the same thing that we wrote.\n");


	// Here, we are reading the bytes into an array. This means that
	// the first byte (0xef, if we wrote the file on a little-endian
	// machine) will be stored in the first element of the array.
	int8_t fromFileArray[4] = { 0,0,0,0 };
	fs = fopen(FILENAME, "r");
	printf("Reading 4 bytes into an array.\n");
	fread(&fromFileArray, 1, 4, fs);
	fclose(fs);
	if(fromFileArray[0] == (int8_t) 0xef)
		printf("0xef was the first byte in the array\n");


	/* Converting endianness: */
	/* One of the most common requirements is to switch between the
	   endianness of your computer (big endian, little endian, or
	   something else) to "network byte order" (aka big endian). C
	   provides functions for this. Although they have cryptic-looking
	   names, 'h' basically means 'host byte order' and 'n' means
	   'network byte order'.  */

	// Host to network conversion
	// uint32_t htonl(uint32_t hostlong);
	// uint16_t htons(uint16_t hostshort);
	// uint32_t ntohl(uint32_t netlong);
	// uint16_t ntohs(uint16_t netshort);

	// Network to host conversion:
	// uint32_t htonl(uint32_t hostlong);
	// uint16_t htons(uint16_t hostshort);
	// uint32_t ntohl(uint32_t netlong);
	// uint16_t ntohs(uint16_t netshort);

	printf("\n");
	printf("We created the file '%s'. You can safely delete it.");
}
