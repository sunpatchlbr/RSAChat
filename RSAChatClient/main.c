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

struct clientinfo {
	char name[10];
	int publicKey;
	int privateP;
	int privateQ;
	int privateE;
	int D;
};

struct serverinfo {
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
	serverAddy.sin_addr.s_addr = inet_pton(AF_INET,argv[2]);// use address string from arg2
	

	//begin setting up socket for use with a single client
	if (argc == 3)	{
		int sockfd; //calling socket()
		if ( ( sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) ) > -1 ) {//create generic sockaddr structure from the sockaddr_in at the address we made
			if ( connect(sockfd, (struct sockaddr*)&serverAddy, NULL)) {
				printf("connected to");
				printf("%d", serverAddy.sin_addr.s_addr);
				printf("sending nickname and public key");
				//send nickname as first line
				//send public key as second line

				//start readwrite loop
			}
			else {
				printf("could not connect\n");
				return -1;
			}
		}
		else {
			printf("Error, socket couldn't be created\n");
			return -1;
		}
	}
	else {
		printf("Error, not enough arguments\n");
		return -1;
	}
} 
