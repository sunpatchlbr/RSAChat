//An attempt at a chat server using RSA Encryption

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//argument is port to host over

struct serverinfo {
	char name[10];
	int publicKey;
	int privateP;
	int privateQ;
	int privateE;
	int D;
};

struct clientinfo {
	char name[10];
	int sock;
	int publicKey;
};

int main(int argc, const char *argv[]) {
	
	//set up address struct

	struct sockaddr_in serverAddy;
	
	//use internet address structure from inet/in.h
	serverAddy.sin_family = AF_INET;
	serverAddy.sin_port = htons(atoi(argv[1])); //use port from argument
	serverAddy.sin_addr.s_addr = INADDR_ANY;
	

	//begin setting up socket for use with a single client
	if (argc != 2)	{
		printf("Error, expected 2 arguments\n");
		exit(0);
	}

	int sockfd; //calling socket()
	
	//create generic sockaddr structure from the sockaddr_in at the address we made
	if ( ( sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ) != 0 ) { 
		printf("Error, socket couldn't be created\n");
		exit(-1);
	}

	printf("socket created on fd %d\n", sockfd);

	//bind the addres to the sock fd
	if (bind(sockfd, (const struct sockaddr*)&serverAddy, sizeof(serverAddy) ) != 0) {
		printf("Error, address could not be bound to socket\n");
		exit(-1);
	}

	printf("bound sockfd %d\n", sockfd);
	
	//now we listen
	if ( listen(sockfd, 1 ) !=  0 ) {
		printf("Error, listen failure\n");
		exit(-1);
	}

	printf("listening on port ");
	printf("%d\n",atoi(argv[1]));
	
	int newsockfd;
	struct sockaddr_in clientAddy;

	if ( (newsockfd = accept(sockfd, (struct sockaddr*)&clientAddy, NULL)) != 0 ) {
		printf("accept failure\n");
		exit(-1);
	}

	printf("accepted connection from");
	printf("%d", clientAddy.sin_addr.s_addr);
	printf("sending nickname and public key");


	//send nickname as first line
	//send public key as second line

	//start readwrite loop
} 
