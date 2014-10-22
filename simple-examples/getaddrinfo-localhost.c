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

int main(void)
{
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // if hostname==NULL and AI_PASSIVE flag is used, getaddrinfo() returns an addrinfo suitable for a server to use.

	// Since node/hostname (first parameter) is NULL and the
	// AI_PASSIVE flag is set, the following getaddrinfo() call
	// creates a socket suitable for a server process to listen on.
	int status = getaddrinfo(NULL, "2222", &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	printf("IP addresses for a socket we are listening on:\n\n");

	for(struct addrinfo *p = res; p != NULL; p = p->ai_next)
	{
		char *ipver = NULL;
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
	}

	freeaddrinfo(res); // free the linked list

	return 0;
}
