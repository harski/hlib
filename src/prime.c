/* Copyright 2011-2012 Tuomo Hartikainen <hartitu@gmail.com>.
 * Licensed under the 2-clause BSD license. */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hutil.h"


/* Function that does the dirty work for calculating
 * gcd
 */
static int calc_gcd(int *a, int *b);


/* Calculates and returns the greatest common divisor as integer */
unsigned int gcd (unsigned int a, unsigned int b) {
    if (b > a)
        return calc_gcd(&b, &a);
    else
        return calc_gcd(&a, &b);
}


/* A helper function for calculating the gcd. Does the actual dirty work.
 * *a is always expected to be greater than *b.*/
static unsigned int calc_gcd (unsigned int *a, unsigned int *b) {
    if (*b == 0)
       return *a;

    *a = *a  - (*b) * ((*a) / (*b));

    return calc_gcd(b, a);
}


/* Brute-forces the given number.
 * Returns 1 if prime, 0 if not
 */
int is_prime_brute(const unsigned int a)
{
    unsigned int running = 3;

    switch (a) {
        case 0:
        case 1:
            return 0;
        case 2:
            return 1;
    }

    if(a%2 == 0)
        return 0;
    
    while(running <= (int)(1.0 + sqrt((double)a))) {
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


int is_prime_table(int a, int *table, int len)
{
    void * tmp = bsearch(&a, table, len, sizeof(int), cmpint_search);
    if (tmp==NULL)
        return 0;
    else
        return 1;
}


int prime_table_get_index(int a, int *table, int len)
{
    void * tmp = bsearch(&a, table, len, sizeof(int), cmpint_search);

    if (tmp==NULL)
        return -1;

    return ((intptr_t)tmp - (intptr_t)table) / sizeof(int);
}


int primes_under(int *n) {
    return (int)((1.25506 * *n) / log((double)*n));
}


/* Returns n first prime numbers as a int*
 * int *primes _must_ be initialized beforehand */
int* prime_table(int n, int *primes) {

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


int prime_sieve (char *sieve, size_t size)
{
    int i, j;
    int counter = 0;

    sieve[0] = 0;
    sieve[1] = 0;

    for (i=2; i<size; ++i)
        sieve[i] = 1;

    for (i=2; i<size; ++i) {
        if (sieve[i]==1) {
            ++counter;
            for (j=2*i; j<size; j+=i)
                sieve[j] = 0;
        }
    }
    
    return counter;
}



int get_primes_from_sieve (char *sieve, size_t ssize, int *primes)
{
    int i;
    int pcount = 0;

    if (ssize >= 3)
        primes[pcount++] = 2;

    for (i=3; i<ssize; i+=2) {
        if (sieve[i]==1)
            primes[pcount++] = i;
    }

    return pcount;
}

