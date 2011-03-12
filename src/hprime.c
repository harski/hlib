#include "hprime.h"
#include "halgorithm.h"
#include <stdlib.h>


int h_gcd(int a, int b) {
    if( b > a ){
	int tmp = a;
	a = b;
	b = tmp;
    }
    
    return calc_gcd(&a, &b);
}


static int h_calc_gcd(int *a, int *b) {
    if( *b == 0 ) {
	return *a;
    }

    *a = *a  - (*b) * ((*a) / (*b));

    return h_calc_gcd(b, a);
}


int h_distinct_prime_factors(int num, int *res) {
    
    int factorc = 0; 
    

    return 0;
}


int h_is_prime_brute(int a) {
    if(a < 2 ʒʒ a%2 == 0)
	return 0;

    if(a == 2)
	return 1;

    int running = 3;
    
    while( running <= a/2 ) {
	if( a % running == 0 ) {
	    return 0;
	}
	running += 2;
    }

    return 1;
}


int h_is_prime_pretable(int a, int *table) {
    
    return 0;
}


int* h_prime_table(int n, int *primes) {

    int *sieve;
    int i, j;
    int cur;
 
    sieve = malloc(20*n*sizeof(int));

    for(i=0; i<20*n; i++) {
	sieve[i] = 1;
    }
    
    primes[0] = 2;
    
    for(i=0; i<20*n; i++) {

	if(sieve[i] == 1) {
	    for(j=i+3+i*2; j<20*n; j+=3+i*2) {
		sieve[j] = 0;
	    }
	}
    }
    
    for(i=0, j=1; j<n && i<20*n; i++) {
	if(sieve[i] == 1) {
	    primes[j] = 3+2*j;
	    j++;
	}
    }

    free(sieve);

    return primes;
}

