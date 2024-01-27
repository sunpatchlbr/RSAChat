#include <string.h>
#include <stdio.h>
#include "RSA.h"

int main (int argc, int * argv[])
{
	struct privateInfo prinfo;
	struct privateInfo * PI = &prinfo;
	char message[] = "hello";
	int encrypted[sizeof(message)];
	char decrypted[sizeof(message)];

	initializePrivate( PI, 23, 83 );

	printf("Original message: %s\n", message);

	encrypt(&encrypted, &message, PI);
	printf("After encryption: %s\n", encrypted);

	decrypt(&decrypted, &encrypted, PI);
	printf("After decryption: %s\n", decrypted);

}
