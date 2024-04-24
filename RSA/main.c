#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"

int main (int argc, char * argv[])
{
	struct privateInfo PI;
	char input[] = "banana";
	int messagelength = sizeof(input)/sizeof(char);
	int cipher[messagelength];
	char message[messagelength];
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	initializePrivate( (struct privateInfo*) &PI, a, b);
	printf("Original: %s\n", input);
	encrypt(cipher, input, messagelength, (struct privateInfo*) &PI);
	printf("Cipher: %d\n", cipher[0]);
	decrypt(message, cipher,  messagelength, (struct privateInfo*) &PI);
	printf("Message after decryption: %s\n", message);

}
