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
	struct sockaddr_un local, remote;

	/*
	  A call to socket() with the proper arguments creates the Unix
	  socket.

	  The second argument, SOCK_DGRAM, tells socket() a datagram
	  socket. The number of read() or recv() must match the number of
	  send() or write(). If you read with a size smaller than the size
	  of the packet, you won't receive the entire message.

	  One more note: all these calls return -1 on error and set the
	  global variable errno to reflect whatever went wrong. Be sure to
	  do your error checking.
	*/
	int s = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (s == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/*
	  You got a socket descriptor from the call to socket(), now you
	  want to bind that to an address in the Unix domain. (That
	  address, is a special file on disk.)

	  This associates the socket descriptor "s" with the Unix socket
	  address "/home/beej/mysocket". Notice that we called unlink()
	  before bind() to remove the socket if it already exists. You
	  will get an EINVAL error if the file is already there.
	*/
	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH_SERVER);
	unlink(local.sun_path);
	int len = strlen(local.sun_path) + sizeof(local.sun_family);
	if (bind(s, (struct sockaddr *)&local, len) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	// What address are we sending the packets to?
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH_CLIENT);

	// Don't have to call listen() for a datagram connection.

	for(;;)
	{
		// don't have to accept() or wait for a connection, just wait
		// for datagrams...
		
		printf("Waiting for a datagram...\n");

		int done = 0;
		do
		{
			char str[101];
			socklen_t remoteLen = (socklen_t) sizeof(struct sockaddr_un);
			int n = recvfrom(s, str, 100, 0, (struct sockaddr*)&remote, &remoteLen);
			if( n < 0)
			{
				perror("recvfrom");
				done = 1;
			}
			else if(n == 0)
				done = 1;
			else
			{
				// recvfrom() reads bytes, and so it has no reason to
				// put a null terminator at an end. So, we need to add
				// a null terminator.
				str[n] = '\0';
				// NOTE: The newline gets sent over to us from the client.
				printf("Datagram contained: %s", str);
				printf("Length of string was: %zu\n", strlen(str));
			}
			
		} while (!done);

		close(s);
	}

	return 0;
}
