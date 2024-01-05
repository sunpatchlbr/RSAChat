//An attempt at a chat server using RSA Encryption

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

//argument is port to host over

struct Server {
	char name[10];
	int publicKey;
	int privateP;
	int privateQ;
	int privateE;
	int D;
};

struct Client {
	char name[10];
	int sock;
	int publicKey;
};

int main(int argc, char *argv[]) {
	
	if (argc == 1)	{
		int sock; //calling socket()
		if ( sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) == 1 ) {
			if () {
			}
			else {
				printf("could not bind");
				return -1;
			}
			return 0;
		}
		else {
			printf("Error, socket couldn't be created");
			return -1;
		}
	}
	else {
		printf("Error, port number expected as argument");
		return -1;
	}
} 
