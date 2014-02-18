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

void example_setsockopt(int sock)
{
	/* This section of code is not strictly necessary for a server.
	 * It eliminates a problem where you run your server, kill it, and
	 * run it again on the same port but the call to bind() produces
	 * an error.  The solution is to add this line of code or to wait
	 * a couple of minutes before running the server again.  The
	 * problem is that the server's socket gets stuck in the TIME_WAIT
	 * state even though the server has been killed.  When the server
	 * restarts, it is unable to acquire that socket again unless you
	 * wait for a long enough time. */
	int yes = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0)
	{
		perror("server: setsockopt() failed: ");
		exit(EXIT_FAILURE);
	}
}

void example_bind(int sock, struct addrinfo *ai)
{
	if(bind(sock, ai->ai_addr, ai->ai_addrlen) == -1)
	{
		perror("server: bind() failed: ");
		exit(EXIT_FAILURE);
	}
}

void example_listen(int sock, int queueSize)
{
	/* Listen for incoming connections on the socket */
	if(listen(sock, queueSize)==-1)
	{
		printf("server: listen() failed: ");
		exit(EXIT_FAILURE);
	}
}



int main(void)
{
	char *port = "8080"; // can also be a name in /etc/services

	// getaddrinfo(): network address and service translation:
	struct addrinfo *socketaddrinfo = example_getaddrinfo(NULL, port);

	// socket(): create an endpoint for communication
	int sock = example_socket(socketaddrinfo);

	example_setsockopt(sock);
	example_bind(sock, socketaddrinfo);
	example_listen(sock, 128);
	freeaddrinfo(socketaddrinfo); // done with socketaddrinfo

	printf("Press Ctrl+C to exit server.\n");
	printf("Point your web browser to: http://127.0.0.1:%s\n", port);
	
	while(1)
	{
		// Get a socket for a particular incoming connection.
		int newsock = accept(sock, NULL, NULL);
		if(newsock == -1)
		{
			perror("accept(): ");
			continue; // try again if accept failed.
		}

		char http_body[] = "hello world";
		char http_headers[1024];
		snprintf(http_headers, 1024,
		         "HTTP/1.0 200 OK\r\n"
		         "Content-Length: %zu\r\n"
		         "Content-Type: text/html\r\n\r\n",
		         strlen(http_body));

		// Return value for send() might indicate an error (we're ignoring it!)
		send(newsock, http_headers, strlen(http_headers), 0);
		send(newsock, http_body, strlen(http_body), 0);
		close(newsock);
	}
}
