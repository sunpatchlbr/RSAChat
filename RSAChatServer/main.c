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

int main(int argc, char *argv[]) {
	
	//set up address struct

	struct sockaddr_in serverAddy;

	serverAddy.sin_family = AF_INET;
	serverAddy.sin_port = htons();
	serverAddy.sin_addr.s_addr = INADDR_ANY;
	

	//begin setting up socket for use with a single client
	if (argc == 1)	{
		int sockfd; //calling socket()
		if ( sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) == 0 ) {
			if (bind(sockfd, serverAddy, sizeof(serverAddy) ) == 0) {
				//bind successful
				if ( listen(sockfd, 1 ) == 0 ) {
					if ( accept(sockfd, NULL, NULL) == 0 ) {
						
					}
					else {
						printf("couldn't accept\n");
					}
				}
				else {
					printf("couldn't listen\n");
				}
			}
			else {
				printf("could not bind\n");
				return -1;
			}
			return 0;
		}
		else {
			printf("Error, socket couldn't be created\n");
			return -1;
		}
	}
	else {
		printf("Error, port number expected as argument\n");
		return -1;
	}
} 
