//An attempt at a chat server using RSA Encryption

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//argument is port to host over

int main(int argc, const char *argv[]) {
	
	//check if argument is entered
	if (argc != 2)	{
		printf("Error, expected PORT as second argument\n");
		exit(0);
	}


	//set up address struct

	struct sockaddr_in serverAddy, clientAddy;
	
	//use internet address structure from inet/in.h
	serverAddy.sin_family = AF_INET;
	serverAddy.sin_port = htons(atoi(argv[1])); //use port from argument
	serverAddy.sin_addr.s_addr = htonl(INADDR_ANY);	

	int sockfd; //socket file descriptor
	
	printf("\nCreating socket to use for chat...\n");

	//create generic sockaddr structure using sockstream from the sockaddr_in at the address we made
	if ( ( sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ) == -1 ) { 
		printf("Error, socket couldn't be created\n");
		exit(-1);
	}
	
	printf("socket created on fd %d\n", sockfd);

	//bind the addres to the sock fd
	if ( bind(sockfd, (struct sockaddr*)&serverAddy, sizeof(serverAddy) ) != 0) {
		printf("Error, address could not be bound to socket\n");
		exit(-1);
	}

	printf("bound address to sockfd %d\n", sockfd);
	
	//now we listen
	if ( listen(sockfd, 1 ) !=  0 ) {
		printf("Error, listen failure\n");
		exit(-1);
	}

	printf("listening on port ");
	printf("%d\n",atoi(argv[1]));
	
	int newsockfd;
	socklen_t clientlen = sizeof(clientAddy);
	if ( ( newsockfd = accept(sockfd, (struct sockaddr*)&clientAddy, &clientlen) ) <  -1 ) {
		printf("accept failure\n");
		exit(-1);
	}

	char clientString[INET_ADDRSTRLEN];
	//create a string of the ipv4 address
	inet_ntop(AF_INET, &clientAddy.sin_addr, clientString, sizeof(clientString));

	printf("accepted connection from address: %s\n", clientString);
	printf("beginning read write loop\n\n");

	int n;
	int count = 0;
	char buffer[140];
	for(;;) {
		n = 0;
		bzero(buffer,140);
		read(newsockfd, buffer, 140); //read what client has said
		printf("%d READ: %s\n", count, buffer);
		
		if ( strncmp("EXIT", buffer, 4) == 0) {
			printf("Client Exiting...");
			break;
		}

		bzero(buffer, 140);
		printf("%d WRITE: ", count++);
		while( n < 140 && (buffer[n++] = getchar()) != '\n')
			;
		write(newsockfd, buffer, 140); //write buffer to socketfd
		
		printf("\n\n");

		if ( strncmp("EXIT", buffer, 4) == 0) {
			printf("Server Exiting...");
			break;
		}
	}

	close(sockfd);
	exit(0);
} 
