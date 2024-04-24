#include "RSA.h"
#include <math.h>
//RSA.c

//Euclidean algorithm
//returns the GCD of the two original inputs
//should return 1 for our prime p and q
//a should be less than b initially
int E(int a, int b)
{
	if(a == 0)
		return b;
	else
	{
		return E(b % a, a);
	}
}


//Extended Euclidean
//similar to one above but we must also change the
//coefficients as we build back up

//GCD = ax + by
int EE(int a, int b, int * x, int * y)
{
	//base case, we hit zero at the stopping point
	//so we must assign 1 as the current coefficient
	// for b
	if(a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}
	
	int xi, yi; // current values for coefficients

	//recursively call EE to find next level
	//b%a is the new a
	//a is the new b
	int GCD = EE( b%a, a, &xi, &yi);
	
	//ax + by = GCD(a,b) (bezout's theorem)
	//GCD(a,b) = GCD(b%a,a) (euclidean alg)
	//ax + by = (b%a)xi + a(yi) (rhs as a linear comb)
	//ax + by = (b - [b/a] * a)xi + ayi (simplify %)
	//ax + by = a(yi - [b/a] * xi) + bx1 (redistribute)
	
	//inductive step/recursive step derived from above
	*x = yi - (b/a) * xi;
	*y = xi;

	return GCD;
}

//used to turn char message into integer cipher
void encrypt( int cipher[], char message[], int messagelength, struct privateInfo * PI )
{
	int intmessage[messagelength];
	printf("\nsize: %d\n", messagelength);
	for(int i = 0; i < messagelength; i++)
	{
		intmessage[i] = (int)message[i];
		printf("%d: %d, %d\n",i,message[i],intmessage[i]);		
	} // pull the chars into ints for bigger size
	printf("\nmessage: %s\n",message);
	crypt(cipher, intmessage, messagelength, PI->n, PI->e);
	printf("\nmessage after crypt()\n");
	for(int i = 0; i < messagelength; i++)
	{
		printf("%d: %d, %d\n",i,message[i],cipher[i]);		
	}
	printf("\n");
}


//used to turn integer cipher into a decrypted char message
void decrypt( char message[], int cipher[], int messagelength, struct privateInfo * PI )
{
	int intmessage[messagelength];
	crypt(intmessage, cipher, messagelength, PI->n, PI->d);
	for(int i = 0; i < messagelength; i++)
	{
		message[i] = (char)intmessage[i];
		printf("intmessage[%d] : %d\n",i,intmessage[i]);
	} // pull the chars into ints for bigger size
}



//use n
//use e as x for encrypting the message
//use d as x for decrypting the cipher
void crypt ( int target[], int initial[], int size, int n, int x)
{
	for(int i = 0; i < size; i++)
	{
		target[i] = powermod(initial[i], x, n);
	}
}

//find (x^y)%p
int powermod(long long  x, unsigned int y, int p)
{
	int res = 1;
	x = fmod(x,p);
	
	if ( x == 0 ) return 0;

	while ( y > 0 )
	{
		if( y & 1 )
			res = fmod((res*x),p);

		y = y >> 1; 
		x = fmod((x*x),p);	
	
	}

	return res;
}

//iterative power
int powit(int x, int y)
{	
	//initial value
	int z = 1;
	while (y>0)
	{
		//if current exponent is odd,
		//use multiply by current base
		if (y&1)
			z = z * x;
		//half exponent
		y = y>>1;
		//square current base
		x = x*x;
	}
	return z;
}

//initialize a privateInfo struct
void initializePrivate(struct privateInfo * PI, int p, int q)
{
	PI->p = p;
	PI->q = q;
	PI->n = p * q;
	PI->e = 5; //use 3 as e for now, fastest
	int phin = (p-1) * (q-1);
	int k, d;//temporary	
	
	//use phin as b (bigger), k is coefficient for phin
	//use e as a (smaller), 
	//d is coefficient(modular inverse) for e
	//call extend euclidean to find the private key d
	EE(PI->e, phin, &d, &k);
	if(d < 0)
	{
		d = phin + d;
	}
	PI->d = d; //assign value of d to PI for private key
	PI->k = k;

	printf("p = %d\nq = %d\nn = %d\ne = %d\nphin = %d\nk = %d\nd = %d\n",
	  PI->p,PI->q,PI->n,PI->e,phin,PI->k,PI->d);
}
