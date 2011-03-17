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


int h_distinct_prime_factors(int num, int *res, int* table, int* table_len) {
    
    int factor_c = 0; 
    int pos;
    int res_size = 20;
    int i;

    free(res);
    res = malloc(res_size*sizeof(int));

    /* TODO: Fix this mess! */

    while( ! ( pos = h_bin_search(table, *table_len , num)) ) {
	res[factor_c++] = table[pos];
	if( factor_c == res_size-1 ) {
	    
	    /* update array size */
	    int *temp = malloc(2*res_size*sizeof(int));
	    for( i=0; i<factor_c; i++ ) {
		temp[i] = res[i];
	    }
	    
	    free(res);
	    res = temp;
	}
    }
    
    res[factor_c++] = table[pos];

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

