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

#define SOCK_PATH "unix-stream-server.temp"

int main(void)
{
	struct sockaddr_un local, remote;

	/*
	  A call to socket() with the proper arguments creates the Unix
	  socket.

	  The second argument, SOCK_STREAM, tells socket() to create a
	  stream socket. Yes, datagram sockets (SOCK_DGRAM) are supported
	  in the Unix domain, but I'm only going to cover stream sockets
	  here. For the curious, see Beej's Guide to Network Programming
	  for a good description of unconnected datagram sockets that
	  applies perfectly well to Unix sockets. The only thing that
	  changes is that you're now using a struct sockaddr_un instead of
	  a struct sockaddr_in.

	  One more note: all these calls return -1 on error and set the
	  global variable errno to reflect whatever went wrong. Be sure to
	  do your error checking.
	*/
	int s = socket(AF_UNIX, SOCK_STREAM, 0);
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
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	int len = strlen(local.sun_path) + sizeof(local.sun_family);
	if (bind(s, (struct sockaddr *)&local, len) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	/*
	  listen() instructs the socket to listen for incoming connections
	  from client programs.
	   
	 The second argument, 5, is the number of incoming connections
	 that can be queued before you call accept(), below. If there are
	 this many connections waiting to be accepted, additional clients
	 will generate the error ECONNREFUSED.
	*/
	if (listen(s, 5) == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for(;;)
	{
		printf("Waiting for a connection...\n");

		/*
		accept() will accept a connection from a client. This
		function returns another socket descriptor! The old descriptor
		is still listening for new connections, but this new one is
		connected to the client.
		
		When accept() returns, the remote variable will be filled with
		the remote side's struct sockaddr_un, and len will be set to
		its length. The descriptor s2 is connected to the client, and
		is ready for send() and recv(), as described in the Network
		Programming Guide.
		*/
		socklen_t remotesize = sizeof(remote);
		int s2 = accept(s, (struct sockaddr *)&remote, &remotesize);
		if (s2 == -1)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}

		printf("Connected.\n");

		int done = 0;
		do
		{
			char str[100];
			int n = recv(s2, str, 100, 0);
			if (n < 0)
			{
				perror("recv");
				done = 1;
			}
			else if(n == 0)
				done = 1;

			if (!done)
			{
				if (send(s2, str, n, 0) < 0)
				{
					perror("send");
					done = 1;
				}
			}
		} while (!done);

		close(s2);
	}

	return 0;
}
