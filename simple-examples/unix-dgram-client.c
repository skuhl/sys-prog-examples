// Based on: http://beej.us/guide/bgipc/output/html/multipage/unixsock.html (code from "Beej's Guide to Network Programming" is public domain).
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

#define SOCK_PATH_SERVER "unix-dgram-server.temp"
#define SOCK_PATH_CLIENT "unix-dgram-client.temp"

int main(void)
{
	struct sockaddr_un remote;
	struct sockaddr_un local;

	// Create a socket - the only information is the type of socket we
	// want to create, not the address we want to connect to.
	int s;
	if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// Set up the address of the socket for our address.
	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH_CLIENT);
	unlink(local.sun_path);
	int len = strlen(local.sun_path) + sizeof(local.sun_family);
	if (bind(s, (struct sockaddr *)&local, len) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	// What address are we sending the packets to?
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH_SERVER);


	// Use send() and recv() to send and receive information on the
	// socket. Note that send(?, ?, ?, 0) is equivalent to write(?, ?,
	// ?). Similarly, recv(?, ?, ?, 0) is the same as read(?, ?, ?).
	//
	// Print a prompt, read a line of text that the user types in.
	char str[100];
	while(printf("> "), fgets(str, 100, stdin), !feof(stdin))
	{
		if (sendto(s, str, strlen(str), 0,
				   (struct sockaddr*) (&remote),
				   (socklen_t) sizeof(struct sockaddr_un)) == -1)
		{
			perror("sendto");
			exit(EXIT_FAILURE);
		}
		printf("sent %zu bytes\n", strlen(str));

	}

	close(s);

	return EXIT_SUCCESS;
}
