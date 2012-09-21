/* Copyright 2012 Tuomo Hartikainen <hartitu@gmail.com>.
 * Licensed under the 2-clause BSD license. */


#include <stdlib.h> /* size_t */
#include "hutil.h"

/* This function may only be used if x<sieve_len, or x is a prime */
unsigned int phi_recursive (unsigned int *phis, size_t phis_len,
                            const char *sieve, size_t sieve_len,
                            const unsigned int x)
{
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

        phis[x] = phi;
        return phi;
    }

    /* If it is known whether n is a prime or not */
    if (x<sieve_len) {
        if (sieve[x]) {
            return x-1;
        } else {
            unsigned int n;
            unsigned int phi;

            /* find a prime divisor */
            unsigned int m;
            for (m=3; m<x; ++m) {
                if (!sieve[m])
                    continue;

                if (x%m==0)
                    break;
            }

            n = x/m;
            if (n%m==0) {
                phi = phi_recursive(phis, phis_len, sieve, sieve_len, n) * m;
                phis[x] = phi;
                return phi;
            } else {
                phi = phi_recursive(phis, phis_len, sieve, sieve_len, n) *
                      phi_recursive(phis, phis_len, sieve, sieve_len, m);
                phis[x] = phi;
                return phi;
            }

        }
    }
    
    /* Now, what to do when the sieve is too small, i.e.
     * we don't know if x is a prime or not... */
    if (is_prime_brute(x))
        return x-1;

    return 0;
}

