//An attempt at a chat server using RSA Encryption

#include <stdio.h>
#include <string.h>

//argument is port to host over

struct Client {
	char name[10]
	int socket = -1;
	int publicKey = 1;
}

int main(int argc, char *argv[]) {
	
	if (argc == 1)	{
		//socket

		//bind

		//listen

		//accept

		//fork to allow concurrent clients
		
		//ask for name and public key to send to others

		//give them a "waiting string" while waiting for 2 clients to join

		//once 2 are connected, give each other their public keys
		//read write loop for each client sending encrypted data back and forth

		//close
		return 0;
	}
	else {
		printf("Error, port number expected as argument");
		return -1;
	}
} 
