#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "hprime.h"


/* Function that does the dirty work for calculating
 * gcd
 */
static int h_calc_gcd(int *a, int *b);


/* Calculates and returns the greatest common divisor as integer */
int h_gcd(int a, int b) {
    if (b > a) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    
    return h_calc_gcd(&a, &b);
}


/* A helper function for calculating the gcd. Does the actual dirty work */
static int h_calc_gcd(int *a, int *b) {
    if (*b == 0)
       return *a;

    *a = *a  - (*b) * ((*a) / (*b));

    return h_calc_gcd(b, a);
}


/* Brute-forces the given number.
 * Returns 1 if prime, 0 if not
 */
int h_is_prime_brute(int a) {
    if(a == 2)
        return 1;

    if(a < 2 || a%2 == 0)
        return 0;

    int running = 3;
    
    while(running <= a/2) {
        if( a % running == 0 )
            return 0;

        running += 2;
    }

    return 1;
}


int cmpint_search (const void *key, const void *x)
{
    return *(int *)key - *(int *)x;
}


int h_is_prime_table(int a, int *table, int len)
{
    void * tmp = bsearch(&a, table, len, sizeof(int), cmpint_search);
    if (tmp==NULL)
        return 0;
    else
        return 1;
}


int h_prime_table_get_index(int a, int *table, int len)
{
    void * tmp = bsearch(&a, table, len, sizeof(int), cmpint_search);

    if (tmp==NULL)
        return -1;

    return ((intptr_t)tmp - (intptr_t)table) / sizeof(int);
}


int h_primes_under(int *n) {
    return (int)((1.25506 * *n) / log((double)*n));
}


/* Returns n first prime numbers as a int*
 * int *primes _must_ be initialized beforehand */
int* h_prime_table(int n, int *primes) {

    int *sieve;
    int i, j, p;
    int upper_bound;

    upper_bound = 20 * n;
 
    sieve = malloc(upper_bound*sizeof(int));

    for (i=0; i<upper_bound; i++) {
        sieve[i] = 1;
    }
    
    primes[0] = 2;
    primes[1] = 3;

    for(i=2; i<n; i++) {
        p = (primes[i-1]-1)/2;

        for(j=p; j<upper_bound; j+=primes[i-1]) {
            sieve[j] = 0;
        }

        while(!sieve[++p]);
        primes[i] = 2*p+1;
    }

    free(sieve);

    return primes;
}

