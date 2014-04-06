/* Based on: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#datagram (code from "Beej's Guide to Network Programming" is public domain).
 */
// Modifications by: Scott Kuhl
//
// This server listens on all available network addresses (IPv4, IPv6)
// using one IPv6 socket. Connections from IPv4 will have addresses
// that look like "::ffff:127.0.0.1". If either IPv4 or IPv6 is
// missing on the machine, this server will listen on whatever is
// available.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#define MYPORT "4950"    // the port users will be connecting to

#define MAXBUFLEN 100

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET forces IPv4; AF_INET6 forces IPv6; AF_UNSPEC allows any
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}


	// loop through all the results and bind to the first we can
	int haveBound = 0;
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(p->ai_family != AF_INET6) // only use IPv6 addresses
			continue;
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
		                                p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		/* This turns V6_ONLY off (which is the default on Linux). We
		 * are setting it to ensure that it is off because different
		 * OS's may default to other values or an OS might have its
		 * default setting modified. */
		int no = 0;     
		if(setsockopt(sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &no, sizeof(int)) == -1) {
			close(sockfd);
			perror("setsockopt");
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("bind");
			continue;
		}
		// If we got here, we successfully bound socket to IPv6 (and,
		// on Linux, this means we also are listening on IPv4 too as
		// long as V6ONLY left to the default value of false).
		haveBound = 1;

		break;
	}

	/* If we didn't bind to an IPv6 address (that is also listening on
	 * IPv4), try binding to IPv4. */
	if(!haveBound)
	{
		for(p = servinfo; p != NULL; p = p->ai_next) {
			if(p->ai_family != AF_INET) // only use IPv4 addresses
				continue;
			
			if ((sockfd = socket(p->ai_family, p->ai_socktype,
			                     p->ai_protocol)) == -1) {
				perror("socket");
				continue;
			}
			if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
				close(sockfd);
				perror("bind");
				continue;
			}
			// If we got here, we successfully bound socket to IPv4 only.
			haveBound = 1;
			break;
		}
	}

	if (p == NULL) {
		fprintf(stderr, "failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	printf("waiting to recvfrom...\n");

	addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
	                         (struct sockaddr *)&their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		exit(1);
	}

	printf("got packet from %s\n",
	       inet_ntop(their_addr.ss_family,
	                 get_in_addr((struct sockaddr *)&their_addr),
	                 s, sizeof s));
	printf("packet is %d bytes long\n", numbytes);
	buf[numbytes] = '\0';
	printf("packet contains \"%s\"\n", buf);

	close(sockfd);

	return 0;
}
