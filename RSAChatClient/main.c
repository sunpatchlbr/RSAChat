//An attempt at a chat server using RSA Encryption

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//argument is port to host over

int main(int argc, const char *argv[]) {

	//begin setting up socket for use with a single client
	if (argc != 3)	{
		printf("Error, expected 3 arguments\n");
		exit(0);
	}
	

	//set up address struct
	struct sockaddr_in serverAddy;
	
	//use internet address structure from inet/in.h
	serverAddy.sin_family = AF_INET;
	serverAddy.sin_port = htons(atoi(argv[1])); //use port from argument
	serverAddy.sin_addr.s_addr = inet_addr(argv[2]); //use IPv4 from argument
	
	int sockfd; // inital socket file descriptor
	
	
	//create generic sockaddr structure from the sockaddr_in at the address we made
	if ( ( sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ) == -1 ) {
		printf("Error, couldn't create socket\n");
		exit(-1);
	}
	
	//bzero(&serverAddy,sizeof(serverAddy));

	if ( connect(sockfd, (struct sockaddr*)&serverAddy, sizeof(serverAddy)) == -1) {
		printf("Error, connect failure\n");
		exit(-1);
	}

	printf("connected\n\n\n"); // to %s\n", *outAddy);
	
	int n;
	int count = 0;
	char buffer[140];
	for(;;){ // begin read write loop
		bzero(buffer,140);
		n = 0;
		while ( n < 140 && (buffer[n++] = getchar()) != '\n')
			;
		// user input goes to buffer until newline key is pressed
		write(sockfd, buffer, 140);
		read(sockfd, buffer, 140); // read what the server has sent
		printf("%d:%s ( size: %d ) \n", count++, buffer, sizeof(buffer));
		if(strncmp(buffer,"EXIT",4) == 0) {
			printf("Exiting...\n\n");
			break;
		}
	}

	exit(0);
}
