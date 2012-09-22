/* Copyright 2012 Tuomo Hartikainen <hartitu@gmail.com>.
 * Licensed under the 2-clause BSD license. */


#include <math.h>
#include <stdlib.h> /* size_t */
#include "hutil.h"

/* returns 0 if x is prime, or the divisor d */
static unsigned get_divisor (const unsigned x, const char *sieve, size_t sieve_len)
{
    unsigned int d;
    unsigned int sqrt_x = (unsigned int) (1.0 + sqrt((double)x));

    if (x%2==0)
        return 2;

    d = 3;
    while (1) {
        if (d >= sieve_len)
            break;

        if (d >= sqrt_x)
            return 0;

        if (!sieve[d]) {
            d+=2;
            continue;
        } else if (x%d==0) {
            return d;
        }

        d+=2;
    }

    while (d < sqrt_x) {
        if (x%d==0) {
            return d;
        }

        d+=2;
    }

    return 0;
}


/* This function may only be used if x<sieve_len, or x is a prime */
unsigned int phi_recursive (unsigned int *phis, size_t phis_len,
                            const char *sieve, size_t sieve_len,
                            const unsigned int x)
{
    unsigned int divisor;
    unsigned int n;
    unsigned int phi;


    if (!x)
        return 0;

    if (x<3)
        return 1;

    /* If phi is already calculated, return it */
    if (x<phis_len && phis[x])
        return phis[x];

    /* phi(2m): if m even, 2*phi(m)
     *          if m odd,    phi(m) */
    if (x%2==0) {
        unsigned int m = x/2;
        unsigned int phi = phi_recursive (phis, phis_len, sieve, sieve_len, m);
        if (m%2==0)
            phi *= 2;

        if (x<phis_len)
            phis[x] = phi;

        return phi;
    }

    if (x<sieve_len && sieve[x]) {
        phis[x] = x-1;
        return x-1;
    }

    divisor = get_divisor(x, sieve, sieve_len);
    if (!divisor) {
        if (x<phis_len) {
            phis[x] = x-1;
        }
        return x-1;
    }

    /* NOTE: divisor is a prime */
    n = x/divisor;
    if (n%divisor==0) {
        phi = phi_recursive(phis, phis_len, sieve, sieve_len, n) * divisor;

        if (x<phis_len)
            phis[x] = phi;

        return phi;
    } else {
        phi = phi_recursive(phis, phis_len, sieve, sieve_len, n) *
              phi_recursive(phis, phis_len, sieve, sieve_len, divisor);

        if (x<phis_len)
            phis[x] = phi;

        return phi;
    }
}

