/* Copyright 2011-2012 Tuomo Hartikainen <hartitu@gmail.com>.
 * Licensed under the 2-clause BSD license. */

/**
 * \file hutil.h
 * \author Tuomo Hartikainen
 * \date 120930
 * \version 0.1
 * \brief Describes the functions in this library.
 *
 * \mainpage
 * \section intro Introduction
 * This is a miscallaneous utility library aiming to solve various
 * problems I've encoutered in various projects.
 *
 * \section inst Installation
 * \code
 * make
 * make install
 * \endcode
 * See the Makefile for options.
 */

#ifndef HUTIL_H
#define HUTIL_H

#include <stdlib.h>


/* Upper limits for number of primes */
#define H_PRIMES_IN_UINT32 203280221
#define H_PRIMES_IN_INT32 105097565
#define H_PRIMES_IN_UINT64 18446744073709551616
#define H_PRIMES_IN_INT64 9223372036854775808


/**
 * \brief Calculate gcd of two numbers.
 * \param a The first number to calculate the gcd from.
 * \param b The second number to calculate the gcd from.
 * \return The gcd of a and b.
 */
unsigned int gcd (unsigned int a, unsigned int b);


/**
 * \brief Brute force check for primeness of an integer.
 * \param a The number to be checked.
 * \return 1 if a is prime, 0 if it is not.
 * \sa is_prime_table
 * \sa prime_table_get_index
 */
int is_prime_brute (const unsigned int a);


/**
 * \brief Checks if a number is a prime by checking the supplied table.
 *
 * Search for a in table with binary search.
 *
 * \param a The number which primeness is checked.
 * \param primes The array of primes in ascending order.
 * \param psize The length of the prime array.
 * \return 0 if a was not found, 1 if it was.
 */
int is_prime_table (unsigned int a, unsigned int *primes, size_t psize);


/**
 * \brief Raise unsigned int to a unsigned power.
 * \param base The base number.
 * \param exp The exponent.
 * \return The result if it fits to an unsigned int, or 0 if it doesn't.
 */
unsigned int pow_uint (const unsigned int base, const unsigned int exp);


/**
 * \brief Get the index of the given prime number.
 * \param a The prime number to be searched.
 * \param table The array that is searched.
 * \param len The length of the prime array.
 * \return The index of a if it is found, otherwise -1.
 */
int prime_table_get_index (unsigned int a, unsigned int *table, size_t len);


/**
 * \brief Gives an upper limit of how much primes there are below n.
 * \param n The upper limit.
 * \return The upper limit of number of primes below n.
 */
unsigned int primes_under (unsigned int n);


/**
 * \brief Get an array of n first primes.
 * \param n The number of primes to get.
 * \param primes At least n elements long pre-allocated array of integers.
 * \return The filled primes array.
 */
unsigned int *prime_table (unsigned int n, unsigned int *primes);


/**
 * \brief Get size-long sieve of Erathosthenes (a prime sieve).
 *
 * \param sieve Size-long, preallocated char array.
 * \param size The size of the sieve.
 * \return Total number of primes in the sieve.
 */
unsigned int prime_sieve (char *sieve, const size_t size);


/**
 * \brief Get prime numbers from a sieve.
 * \param sieve Sieve containing the primes.
 * \param ssize Size (length) of the sieve.
 * \param primes Pre-allocated, array big enough to hold the primes from the sieve.
 * \return Number of primes in primes (and in sieve).
 */
int get_primes_from_sieve (char *sieve, size_t ssize, unsigned int *primes);


/*******************************************
 * Permutation, originally by Sami Hyvonen
 ******************************************/
int* permutation(int *data, const unsigned int L, const unsigned int N);


/**
 * \brief Calculate phi(x) with a help of precalculated values.
 * \param phis phis_len long array for holding calculated phi values.
 * \param phis_len Length of phis.
 * \param sieve sieve_len long prime sieve.
 * \param sieve_len Length of sieve.
 * \param x The number which phi value is computed.
 * \return Phi value of x.
 * \sa prime_sieve
 */
unsigned int phi_recursive (unsigned int *phis, size_t phis_len,
                            const char *sieve, size_t sieve_len,
                            const unsigned int x);


#endif /* HUTIL_H */

