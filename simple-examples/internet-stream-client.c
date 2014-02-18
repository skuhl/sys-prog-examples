// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>


/* We will use getaddrinfo() to get an addrinfo struct which will
 * contain information the information we need to create a TCP
 * stream socket. The caller should use
 * freeaddrinfo(returnedValue) when the returend addrinfo struct
 * is no longer needed. */
struct addrinfo* example_getaddrinfo(const char* hostname, const char* port)
{
	/* First we need to create a struct that tells getaddrinfo() what
	 * we are interested in: */
	struct addrinfo hints; // a struct 
	memset(&hints, 0, sizeof(hints)); // Set bytes in hints struct to 0
	hints.ai_family = AF_INET;    // AF_INET for IPv4, AF_INET6 for IPv6, AF_UNSPEC for either
	hints.ai_socktype = SOCK_STREAM;  // Use TCP

	// hints.ai_flags is ignored if hostname is not NULL. If hostname
	// is NULL, this indicates to getaddrinfo that we want to create a
	// server.
	hints.ai_flags = AI_PASSIVE; 
	struct addrinfo *result;  // A place to store info getaddrinfo() provides to us.
	
	/* Now, call getaddrinfo() and check for error: */
	int gai_ret = getaddrinfo(hostname, port, &hints, &result);
	if(gai_ret != 0)
	{
		// Use gai_strerror() instead of perror():
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_ret));
		exit(EXIT_FAILURE);
	}
	return result;
}

/* Create a socket. Returns a file descriptor. */
int example_socket(struct addrinfo *ai)
{
	int sock = socket(ai->ai_family,
	                  ai->ai_socktype,
	                  ai->ai_protocol);
	if(sock == -1)
	{
		perror("socket() error:");
		exit(EXIT_FAILURE);
	}
	return sock;
}

void example_connect(int sock, struct addrinfo *ai)
{
	if(connect(sock, ai->ai_addr, ai->ai_addrlen) == -1)
	{
		perror("connect() failure: ");
		exit(EXIT_FAILURE);
	}
}


int main(void)
{
	char *hostname = "www.mtu.edu";
	char *port = "80"; // can also be a name in /etc/services

	// getaddrinfo(): network address and service translation:
	struct addrinfo *socketaddrinfo = example_getaddrinfo(hostname, port);

	// socket(): create an endpoint for communication
	int sock = example_socket(socketaddrinfo);

	// connect(): initiate a connection on a socket
	example_connect(sock, socketaddrinfo);
	freeaddrinfo(socketaddrinfo); // done with socketaddrinfo

	// Send an HTTP request:
	char httpget[1024];
	snprintf(httpget, 1024,
	         "GET / HTTP/1.1\r\n"
	         "Host: %s\r\n"
	         "Connection: close\r\n\r\n",
	         hostname);

	ssize_t s = send(sock, httpget, strlen(httpget), 0);
	if(s == -1)
	{
		perror("send");
		exit(EXIT_FAILURE);
	}
	else if (s < (ssize_t)strlen(httpget))
	{
		printf("Entire message did not get sent.");
	}


	while(1)
	{
		char recvbuf[1024];
		ssize_t recvdBytes = 0;

		recvdBytes = recv(sock, recvbuf, 1024, 0);
		if(recvdBytes > 0) // print bytes we received to console
			fwrite(recvbuf, 1, recvdBytes, stdout);
		else if(recvdBytes == 0) // server closed connection
		{
			fflush(stdout);
			close(sock);
			exit(EXIT_SUCCESS);
		}
		else
		{   // error receiving bytes
			perror("recv:");
			close(sock);
			exit(EXIT_FAILURE);
		}
	}
}
