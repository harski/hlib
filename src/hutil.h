/* Copyright 2011-2012 Tuomo Hartikainen <hartitu@gmail.com>.
 * Licensed under the 2-clause BSD license. */


#ifndef HUTIL_H
#define HUTIL_H

/* Upper limits for number of primes */
#define H_PRIMES_IN_UINT32 203280221
#define H_PRIMES_IN_INT32 105097565
#define H_PRIMES_IN_UINT64 18446744073709551616
#define H_PRIMES_IN_INT64 9223372036854775808


/* Front-end function to call for calculating gcd */
int gcd(int a, int b);


/* Returns 1 if a is prime, 0 if it's not */
int is_prime_brute(int a);


/* Checks if a given number is a prime by checking the table.
 * a is the number to be searched,
 * table is the array of primes,
 * len is the length of the prime table.
 * Returns a non-zero or 0 if depending wether the number was found.
 */
int is_prime_table(int a, int *table, int len);


/* Returns the index of the prime or -1 if it isn't in the table. */
int prime_table_get_index(int a, int *table, int len);

/* Returns the number of primes under n
 * *n is the upper limit
 */
int primes_under(int *n);


/* Returns a table of n first primes
 * n is the number of primes to get
 * primes is the preallocated table of integers
 */
int* prime_table(int n, int *primes);


/* Fills the pre-allocated sieve with 0's and 1's, 1's marking the position of
 * the primes. */
int prime_sieve (char *sieve, size_t size);


/* Fills the pre-allocated prime table with primes, based on the pre calculated
 * sieve.
 * Returns the number of primes found */
int get_primes_from_sieve (char *sieve, size_t ssize, int *primes);


/*******************************************
 * Permutation, originally by Sami Hyvonen
 ******************************************/
int* permutation(int *data, const unsigned int L, const unsigned int N);


#endif /* HUTIL_H */

