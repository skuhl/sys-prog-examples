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
	   It eliminates a problem where you run your server, kill it, and
	   run it again on the same port but the call to bind() produces
	   an error. The solution is to add this line of code or to wait
	   a couple of minutes before running the server again. The
	   problem is that the server's socket gets stuck in the TIME_WAIT
	   state even though the server has been killed. When the server
	   restarts, it is unable to acquire that socket again unless you
	   wait for a long enough time.

	   If you comment out this code and want to see the socket reach
	   the TIME_WAIT state, run your server and run "netstat -atnp |
	   grep 8080" to see the server listening on the port. Next,
	   connect to the server with a client and re-run the netstat
	   command. You will see that the socket remains in the TIME_WAIT
	   state for a while (a couple minutes).
	*/
	int yes = 1;
#if 1
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0)
	{
		perror("server: setsockopt() failed: ");
		close(sock);
		exit(EXIT_FAILURE);
	}
#endif


#if 0
	/* Keepalive periodically sends a packet after a connection has
	 * been idle for a long time to ensure that our connection is
	 * still OK. It typically is not needed and defaults to OFF.

	 http://www.tldp.org/HOWTO/html_single/TCP-Keepalive-HOWTO/
	 http://tools.ietf.org/html/rfc1122
	*/
	
	/* Check the status for the keepalive option */
	int optval;
	socklen_t optlen=sizeof(int);
	if(getsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
		perror("getsockopt()");
		close(sock);
		exit(EXIT_FAILURE);
	}
	printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

	/* Set the option active */
	yes = 1;
		if(setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) < 0) {
			perror("setsockopt()");
			close(sock);
			exit(EXIT_FAILURE);
		}
	printf("SO_KEEPALIVE set on socket\n");
#endif
	
}

void example_bind(int sock, struct addrinfo *ai)
{
	if(bind(sock, ai->ai_addr, ai->ai_addrlen) == -1)
	{
		perror("server: bind() failed: ");
		close(sock);
		exit(EXIT_FAILURE);
	}
}

void example_listen(int sock, int queueSize)
{
	/* Listen for incoming connections on the socket */
	if(listen(sock, queueSize)==-1)
	{
		printf("server: listen() failed: ");
		close(sock);
		exit(EXIT_FAILURE);
	}
}



int main(void)
{
	// We can't listen on a port lower than 1024 unless we are root.
	char *port = "8080"; // can also be a name in /etc/services.

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
		         strlen(http_body)); // should check return value

		if(send(newsock, http_headers, strlen(http_headers), 0) == -1)
		{
			perror("send");
			close(newsock);
			exit(EXIT_FAILURE);
		}
		if(send(newsock, http_body, strlen(http_body), 0) == -1)
		{
			perror("send");
			close(newsock);
			exit(EXIT_FAILURE);
		}

		/* shutdown() (see "man 2 shutdown") can be used before
		   close(). It allows you to partially close a socket (i.e.,
		   indicate that we are done sending data but still could
		   receive). This could allow us to signal to a peer that we
		   are done sending data while still allowing us to receive
		   data. SHUT_RD will disallow reads from the socket, SHUT_WR
		   will disallow writes, and SHUT_RDWR will disallow read and
		   write. Also, unlike close(), shutdown() will affect all
		   processes that are sharing the socket---while close() only
		   affects the process that calls it. */
#if 0
		if(shutdown(newsock, SHUT_RDWR) == -1)
		{
			perror("shutdown");
			close(newsock);
			exit(EXIT_FAILURE);
		}
#endif

		if(close(newsock) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
	}
}
