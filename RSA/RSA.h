#ifndef RSA_H
#define RSA_H

#include <string.h>
#include <stdio.h>

struct privateInfo {
	int p; // must be prime
	int q; // must be prime
	int n; // equal to p*q
	int e; // greater than 1, less than phi of n
	int d; // equal to ( phi(n) * i + 1) / e
}

struct publicInfo {
	int n; //needed for public key, larger the better, so it can't be factored reasonably
	int e;
}

int GCD(int a, int b);

char * encrypt();

#endif
