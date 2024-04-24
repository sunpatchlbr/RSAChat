#ifndef RSA_H
#define RSA_H

#include <string.h>
#include <stdio.h>

struct privateInfo {
	int p; // must be prime
	int q; // must be prime
	int n; // equal to p*q
	int e; // greater than 1, less than phi of n
	int k; // coefficient for phin
	int d; // equal to ( phi(n) * i + 1) / e
};

struct publicInfo {
	int n; //needed for public key, larger the better, so it can't be factored reasonably
	int e;
};

void initializePrivate(struct privateInfo * PI, int p, int q);

//recursively finds GCD
//b should be bigger than a
int E(int a, int b);

// recursively finds and returns d, the private key
int EE(int a, int b, int * x, int * y); //extended eulcidean algorithm for finding d
// first take in phi of n and e
// find GCD of phin and e = 1, so you can get recursively find 1 as a linear combination of phin and e,
// the coeffient of e is going to be the modular inverse of d
// since d*e = 1mod(phi(n))
// d will be that coeffient modphi(n)

void encrypt( int cipher[], char message[], int messagelength, struct privateInfo * PI);

void decrypt(char message[], int cipher[], int messagelength, struct privateInfo * PI);

//use for both encryption and decryption
// C = (M^e)mod(n)
//returns the cipher text
// M = (C^d)mod(n)
// returns the message
void crypt( int target[], int initial[], int size, int n, int x);

//exponential mod
int powermod(long long x, unsigned int y, int p);

//use for exponentiation within crypt()
int powit(int x, int y);

#endif
