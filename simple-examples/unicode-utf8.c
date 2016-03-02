// Scott Kuhl
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(int argc, char *argv[])
{
	/* By default, all C programs start with the "C" locale. Here, we
	 * set the locale to what actually is our "native" locale
	 * supported on this machine. In the US, the locale is often
	 * en_US.UTF-8 which means the US variation of English using the
	 * UTF-8 encoding.
	 *
	 * The man page for setlocale() explains that if the second
	 * parameter is an empty string, setlocale() will set the locale
	 * to the native locale of the machine.
	 *
	 * The main reason we call setlocale() in this in this program is
	 * to simply show you what your locale is set to. If your native
	 * locale is set to something that does not support UTF-8
	 * encoding, then this example might not work (because your
	 * terminal isn't expecting UTF-8)
	 */
	char* l = setlocale(LC_ALL, "");
	if (l == NULL) {
		printf("Locale not set\n");
	} else {
		printf("Locale set to %s\n", l);
	}
	
	// The 'hello' variable is a multibyte UTF-8 encoded string. Note
	// that this .c file is encoded using UTF-8. The compiler will need
	// to recognize that and treat the string as UTF-8.
	//
	// Compilers such as gcc have several options to change how it handles encoding:
	// http://stackoverflow.com/questions/12216946/    
	char *hello = "Helló Ẅorld, here is a beetle: 🐞";
	printf("Our message has 32 characters in it (excluding null terminator)\n");
	printf("Our message has %zu bytes in it (excluding null terminator)\n", strlen(hello)); // Should print 38
    
	// ó uses 2 bytes in UTF-8 encoding
	// Ẅ uses 3 bytes in UTF-8 encoding
	// 🐞 uses 4 bytes in UTF-8 encoding
	// 2+3+4 = 9 bytes for three special characters.
	//
	// So:
	// 32-3 = 29 bytes for ASCII characters
	//      +  9 bytes for 3 special characters
	//      ====
	//        38 bytes needed for string.
    
	// Print all bytes (including null terminator)
	for(unsigned int i=0; i<strlen(hello)+1; i++)
	{
		printf("byte %2d is %4d (unsigned decimal), %2x (hex), and looks like '%c'\n",
		       i, (unsigned char) hello[i], (unsigned char) hello[i], hello[i]);
	}
	printf("Note: We started counting from 0; last byte is the null terminator.\n");

	printf("\n");
	printf("printf(): %s\n", hello);
	
}
