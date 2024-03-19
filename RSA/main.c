#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"

int main (int argc, char * argv[])
{
	struct privateInfo PI;
	char input[] = "hello";
	int encrypted[sizeof(input)];
	int * cipher = encrypted;
	char decrypted[sizeof(input)];
	char * message = decrypted;
	/*
	int x, y;
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int test = EE(a, b, &x, &y);

	printf("(%d)*(%d) + (%d)*(%d) = %d\n",x,a,y,b,test);
	*/
	initializePrivate( (struct privateInfo*) &PI, a, b);

	printf("Input  message: %s\n", input);

	encrypt(cipher, message, PI);
	printf("Cipher after  encryption: %s\n", encrypted);

	//decrypt(&decrypted, &encrypted, PI);
	printf("Message after decryption: %s\n", decrypted);

}
