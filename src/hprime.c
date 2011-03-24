#include "hprime.h"
#include "halgorithm.h"
#include <stdlib.h>


/* Calculates and returns the greatest common divisor as integer */
int h_gcd(int a, int b) {
    if( b > a ){
	int tmp = a;
	a = b;
	b = tmp;
    }
    
    return h_calc_gcd(&a, &b);
}

/* A helper function for calculating the gcd. Does the actual dirty work */
static int h_calc_gcd(int *a, int *b) {
    if( *b == 0 ) {
   	return *a;
    }

    *a = *a  - (*b) * ((*a) / (*b));

    return h_calc_gcd(b, a);
}


/* Brute-forces the given number.
 * Returns 1 if prime, -1 if not
 */
int h_is_prime_brute(int a) {
    if(a < 2 || a%2 == 0)
	return -1;

    if(a == 2)
	return 1;

    int running = 3;
    
    while( running <= a/2 ) {
	if( a % running == 0 ) {
	    return -1;
	}
	running += 2;
    }

    return 1;
}


/* Returns n first prime numbers as a int*
 * int *primes _must_ be initialized beforehand */
int* h_prime_table(int n, int *primes) {

    int *sieve;
    int i, j, p;
 
    sieve = malloc(20*n*sizeof(int));

    for(i=0; i<20*n; i++) {
	sieve[i] = 1;
    }
    
    primes[0] = 2;
    primes[1] = 3;
    for(i=2; i<n; i++) {
	p = (primes[i-1]-1)/2;
	for(j=p; j<20*n; j+=primes[i-1]) {
	    sieve[j] = 0;
	}
	while( !sieve[++p] );
	primes[i] = 2*p+1;
    }

    free(sieve);

    return primes;
}

