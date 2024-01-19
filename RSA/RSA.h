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

//recursively finds GCD
int E(int a, int b);

//
// recursively finds and returns d, the private key
int EE(int phi, int e); //extended eulcidean algorithm for finding d
// first take in phi of n and e
// find GCD of phin and e = 1, so you can get recursively find 1 as a linear combination of phin and e,
// the coeffient of e is going to be the modular inverse of d
// since d*e = 1mod(phi(n))
// d will be that coeffient modphi(n)



// C = (M^e)mod(n)
// returns the cipher text
char * encrypt( char * messagge);

// M = (C^d)mod(n)
// returns the message
char * decrypt( char * cipher);

#endif
