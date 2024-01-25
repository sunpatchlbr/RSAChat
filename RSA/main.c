#include <string.h>
#include <stdio.h>
#include "RSA.h"

int main (int argc, int * argv[])
{
	struct privateInfo * PI;
	char message[] = "hello";
	char encrypted[sizeof(message)];
	char decrypted[sizeof(message)];

	initializePrivate( PI, 23, 83 );

	printf("Original message: %s\n", message);

	crypt(&encrypted, &message, PI.n, PI.e);
	printf("After encryption: %s\n", encrypted);

	crypt(&decrypted, &encrypted, PI.n, PI.d);
	printf("After decryption: %s\n", decrypted);

}
