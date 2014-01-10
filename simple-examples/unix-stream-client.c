// Based on: http://beej.us/guide/bgipc/output/html/multipage/unixsock.html (code from "Beej's Guide to Network Programming is public domain).
// Modifications by: Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "unix-stream-server.temp"

int main(void)
{
	int s, t, len;
	struct sockaddr_un remote;


	// Create a socket - the only information is the type of socket we
	// want to create, not the address we want to connect to.
	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// Connect the socket to an address. The addresses for Unix domain
	// sockets are special filenames.
	printf("Trying to connect...\n");
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}

	printf("Connected.\n");

	// Use send() and recv() to send and receive information on the
	// socket. Note that send(?, ?, ?, 0) is equivalent to write(?, ?,
	// ?). Similarly, recv(?, ?, ?, 0) is the same as read(?, ?, ?).
	//
	// Print a prompt, read a line of text that the user types in.
	char str[100];
	while(printf("> "), fgets(str, 100, stdin), !feof(stdin))
	{
		if (send(s, str, strlen(str), 0) == -1)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}

		if ((t=recv(s, str, 100, 0)) > 0)
		{
			str[t] = '\0';
			printf("echo> %s", str);
		} else
		{
			if (t < 0) perror("recv");
			else printf("Server closed connection\n");
			exit(EXIT_FAILURE);
		}
	}

	close(s);

	return EXIT_SUCCESS;
}
