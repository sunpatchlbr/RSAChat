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
int EE(int a, int * x, int b, int * y)
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
	int GCD = return EE( b%a, a, &xi, &yi);
	
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

char * encrypt ( char * message )
{
	for(;;)
		return 0;
}

char * decrypt ( char * cipher )
{
	for(;;)
		return 0;
}

void initializePrivate(int p, int q)
{
	if ( p == 0 || q == 0 )
	{
		//randomly assign prime numbers
	}
	else
	{
		//use p and q as primes
	}
}
