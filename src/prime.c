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
static unsigned int calc_gcd(unsigned int *a, unsigned int *b);


/* Comparator function for binary search */
static int cmpint_search (const void *key, const void *x);


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


/* Brute-forces the given number. */
bool is_prime_brute (const unsigned int a)
{
    switch (a) {
        case 0:
        case 1:
            return false;
        case 2:
            return true;
    }

    if(a%2 == 0)
        return false;
    
    for (unsigned running = 3; running <= (int)(1.0 + sqrt((double)a)); running += 2) {
        if( a % running == 0 )
            return false;
    }

    return true;
}


static int cmpint_search (const void *key, const void *x)
{
    if (*(unsigned int *)key == *(unsigned int *)x) {
        return 0;
    } else {
        if (*(unsigned int *)key > *(unsigned int *)x)
            return 1;
        else
            return -1;
    }
}


bool is_prime_table (const unsigned int a, const unsigned int *primes, const size_t psize)
{
    void *tmp = bsearch(&a, primes, psize, sizeof(unsigned int), cmpint_search);
    if (tmp==NULL)
        return false;
    else
        return true;
}


int prime_table_get_index (const unsigned int a, const unsigned int *table, const size_t len)
{
    void * tmp = bsearch(&a, table, len, sizeof(unsigned int), cmpint_search);

    if (tmp==NULL)
        return -1;

    return ((intptr_t)tmp - (intptr_t)table) / sizeof(unsigned int);
}


unsigned int primes_under (const unsigned int n)
{
    if (n==0)
        return 0;
    return (unsigned int)((1.25506 * n) / log((double)n));
}


/* Returns n first prime numbers as a int*
 * int *primes _must_ be initialized beforehand */
unsigned int *prime_table (const unsigned int n, unsigned int *primes)
{
    bool *sieve;
    const unsigned int upper_bound = 20*n;

    sieve = malloc(upper_bound*sizeof(bool));

    if (sieve==NULL)
        return NULL;

    for (unsigned int i=0; i<upper_bound; i++)
        sieve[i] = true;
    
    primes[0] = 2;
    primes[1] = 3;

    unsigned int p;
    for (unsigned int i=2; i<n; i++) {
        p = (primes[i-1]-1)/2;

        for(unsigned int j=p; j<upper_bound; j+=primes[i-1])
            sieve[j] = false;

        while (!sieve[++p]);
        primes[i] = 2*p+1;
    }

    free(sieve);

    return primes;
}


unsigned int prime_sieve (bool *sieve, const size_t size)
{
    unsigned int counter = 0;

    sieve[0] = false;
    sieve[1] = false;

    for (unsigned int i=2; i<size; ++i)
        sieve[i] = true;

    for (unsigned int i=2; i<size; ++i) {
        if (sieve[i]) {
            ++counter;
            for (unsigned int j=2*i; j<size; j+=i)
                sieve[j] = false;
        }
    }
    
    return counter;
}


unsigned int get_primes_from_sieve (const bool *sieve, const size_t ssize, unsigned int *primes, const size_t psize)
{
    unsigned int pcount = 0;
    
    if (ssize >= 3 && psize>=1)
        primes[pcount++] = 2;
    else
        return 0;

    for (unsigned int i=3; i<ssize && pcount<psize; i+=2) {
        if (sieve[i])
            primes[pcount++] = i;
    }

    return pcount;
}

