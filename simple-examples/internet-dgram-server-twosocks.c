/* Based on: http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#datagram (code from "Beej's Guide to Network Programming" is public domain).
 */
// Modifications by: Scott Kuhl
//
// This server uses two different sockets --- one for IPv4 and one for
// IPv6.

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
	int sockfd4, sockfd6;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;


	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET forces IPv4; AF_INET6 forces IPv6; AF_UNSPEC allows any
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}


	// loop through all the results and bind to the IPv6 address we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(p->ai_family != AF_INET6) // only use IPv6 addresses
			continue;
		if ((sockfd6 = socket(p->ai_family, p->ai_socktype,
		                      p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		/* This turns V6_ONLY on (which is NOT the default on
		 * Linux). This will make this socket only work with
		 * IPv4. Other OS's might have other defaults. */
		int yes = 1;     
		if(setsockopt(sockfd6, IPPROTO_IPV6, IPV6_V6ONLY, &yes, sizeof(int)) == -1) {
			close(sockfd6);
			perror("setsockopt");
		}
		if (bind(sockfd6, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd6);
			perror("bind");
			continue;
		}
		// If we got here, we successfully bound socket to IPv6.
		break;
	}

	// loop through all the results and bind to the first IPv4 address we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(p->ai_family != AF_INET) // only use IPv4 addresses
			continue;
		if ((sockfd4 = socket(p->ai_family, p->ai_socktype,
		                      p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		if (bind(sockfd4, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd4);
			perror("bind");
			continue;
		}
		// If we got here, we successfully bound an IPv4 socket.
		break;
	}


	if (p == NULL) {
		fprintf(stderr, "failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	printf("Waiting for something to read from either the IPv4 or IPv6 sockets...\n");
	struct pollfd fds[2];
	fds[0].fd = sockfd4;
	fds[0].events = POLLIN;
	fds[1].fd = sockfd6;
	fds[1].events = POLLIN;
	// wait for something to read from
	poll(fds, 2, -1);
	// figure out which socket we can now read from
	int sockfd;
	if(fds[0].revents & POLLIN) {
		printf("Reading from IPv4 socket\n");
		sockfd = sockfd4;
	}
	else {
		printf("Reading from IPv6 socket\n");
		sockfd = sockfd6;
	}
	
	// Read from the socket:
	char buf[MAXBUFLEN];
	socklen_t addr_len = sizeof their_addr;
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

	close(sockfd4);
	close(sockfd6);

	return 0;
}
