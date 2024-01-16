//An attempt at a chat server using RSA Encryption

#include <stdio.h>
#include <string.h>
#include <strings.h>
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
	serverAddy.sin_port = htons(8080);//atoi(argv[1])); //use port from argument
	serverAddy.sin_addr.s_addr = inet_addr("127.0.0.1");
	//inet_pton(AF_INET, argv[2], &serverAddy.sin_addr.s_addr);
	// use address string from arg2 in pton to make the ipv4 address

	//begin setting up socket for use with a single client
	if (argc != 3)	{
		printf("Error, expected 3 arguments\n");
		exit(0);
	}
		
	//printf("port from arg[1]: %s\n", *argv[1]); //print port from arg1
	//char outAddy[INET_ADDRSTRLEN]; // declare string of ipv4 length
	//inet_ntop(AF_INET, &serverAddy.sin_addr, outAddy, INET_ADDRSTRLEN); // use ntop to create a string in outAddy of the ipv4 address
	//printf("address from arg[2]: %s\n", *outAddy);


	int sockfd; //calling socket()
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

	printf("connected\n"); // to %s\n", *outAddy);
	printf("sending nickname and public key");
	//send nickname as first line
	//send public key as second line

	//start readwrite loop
} 
