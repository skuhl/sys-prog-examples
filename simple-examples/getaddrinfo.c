// Based on: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#getaddrinfo (code from "Beej's Guide to Network Programming is public domain).
// Modifications by: Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr,"usage: %s google.com\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // ignored by getaddrinfo() except when host==NULL---for example, when we are trying to start a server.

	// Either the hostname (1st argument) or the port (2nd
	// argument---a string) can be NULL---but both of them cannot be
	// NULL.
	int status = getaddrinfo(argv[1], NULL, &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	printf("IP addresses for %s:\n\n", argv[1]);

	for(struct addrinfo *p = res; p != NULL; p = p->ai_next)
	{
		char *ipver = NULL;

#if 0
		void *addr = NULL;

		// get the pointer to the address itself,
		// different fields in IPv4 and IPv6:
		if (p->ai_family == AF_INET) { // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else { // IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		// convert the IP to a string and print it:
		char ipstr[INET6_ADDRSTRLEN];
		if(inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr) == NULL)
		{
			perror("inet_ntop");
			exit(EXIT_FAILURE);
		}
		printf("  %s: %s\n", ipver, ipstr);
#else
		// An alternative (easier?) way to get IP addresses into a
		// string that we can print:
		if(p->ai_family == AF_INET)
			ipver = "IPv4";
		else if(p->ai_family == AF_INET6)
			ipver = "IPv6";
		else
			ipver = "IPv?";

		char buffer[NI_MAXHOST];
		int err = getnameinfo(p->ai_addr, p->ai_addrlen,
		                      buffer, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		if (err != 0)
			fprintf(stderr, "Error in getnameinfo: %s\n", gai_strerror(err));
		else
			printf("  %s: %s\n", ipver, buffer); // print hostname
#endif
	}

	freeaddrinfo(res); // free the linked list

	return 0;
}
