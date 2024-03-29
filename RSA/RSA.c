#include "RSA.h"
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
void encrypt( int cipher[], char message[], struct privateInfo * PI )
{
	int intmessage[sizeof(message)];
	printf("nsize: %d", sizeof(message));
	for(int i = 0; i < sizeof(*message); i++)
	{
		intmessage[i] = message[i];
		printf("%d: %s, %d",i,message[i],intmessage[i]);		
	} // pull the chars into ints for bigger size
	printf("message: %s\n",message);
	//crypt(cipher, &intmessage, PI->n, PI->e);
}


//used to turn integer cipher into a decrypted char message
void decrypt( char * message[], int * cipher[], struct privateInfo * PI )
{
	int * intmessage[sizeof(*cipher)];
	crypt(intmessage, cipher, PI->n, PI->e);
	for(int i = 0; i < sizeof(*intmessage); i++)
	{
		*message[i] = (*intmessage[i]);
	} // pull the chars into ints for bigger size
}



//use n
//use e as x for encrypting the message
//use d as x for decrypting the cipher
void crypt ( int * target[], int * initial[], int n, int x)
{
	int s = sizeof(*target);
	int m = sizeof(*initial);
	for(int i = 0; i < s && i < m; i++)
	{
		*target[i] = ( powit((*initial[i]), x) ) % n;
	}
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
	PI->e = 2; //use 2 as e for now, fastest
	int phin = (p-1) * (q-1);
	int k, d;//temporary	
	
	//use phin as b (bigger), k is coefficient for phin
	//use e as a (smaller), 
	//d is coefficient(modular inverse) for e
	//call extend euclidean to find the private key d
	EE(PI->e, phin, &d, &k); 
	PI->k = k;
	PI->d = d; //assign value of d to PI for private key
	printf("p = %d\nq = %d\nn = %d\ne = 2\nphin = %d\nk = %d\nd = %d\n",
	  PI->p,PI->q,PI->n,phin,PI->k,PI->d);
}
