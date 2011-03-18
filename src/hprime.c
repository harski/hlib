#include "hprime.h"
#include "halgorithm.h"
#include <stdlib.h>


int h_gcd(int a, int b) {
    if( b > a ){
	int tmp = a;
	a = b;
	b = tmp;
    }
    
    return h_calc_gcd(&a, &b);
}


static int h_calc_gcd(int *a, int *b) {
    if( *b == 0 ) {
   	return *a;
    }

    *a = *a  - (*b) * ((*a) / (*b));

    return h_calc_gcd(b, a);
}

struct h_pf *h_distinct_prime_factors(int num, struct h_pf *pf, struct h_pl *pl) {
    if(num < 2) {
	h_pf_add_factor(pf, num);
    } else {
	int pos = 0;
	/* untill num is a prime */
	while( ( pos = h_bin_search(pl->list, pl->size, num)) < 0) {
	    if( num % pl->list[pos] == 0 ) {
		h_pf_add_unique(pf, pl->list[pos]);
		num /= pl->list[pos];
	    } else {
		pos++;
	    }
	}

	/* add num to factor list */
	h_pf_add_unique(pf, num);
     
    }
    
    return pf;
}


int h_is_prime_brute(int a) {
    if(a < 2 || a%2 == 0)
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


int* h_prime_table(int n, int *primes) {

    int *sieve;
    int i, j;
 
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

struct h_pl *h_prime_table_s(int n, struct h_pl *pl) {
    int *sieve;
    int i, j;
 
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

    h_pl_add_prime(pl, 2);
    
    for(i=0, j=1; j<n && i<20*n; i++) {
	if(sieve[i] == 1) {
	    h_pl_add_prime(3+2*j);
	    j++;
	}
    }

    free(sieve);
    
    return pl;
}

