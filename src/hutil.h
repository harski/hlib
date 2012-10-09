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

#include <stdbool.h>
#include <stddef.h>


/* Upper limits for number of primes */
/**
 * \brief Number of primes in uint32
 */
#define PRIMES_IN_UINT32 203280221

/**
 * \brief Number of primes in int32
 */
#define PRIMES_IN_INT32 105097565

/**
 * \brief Number of primes in uint64
 */
#define PRIMES_IN_UINT64 18446744073709551616

/**
 * \brief Number of primes in int64
 */
#define PRIMES_IN_INT64 9223372036854775808


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
 * \return true or false.
 * \sa is_prime_table
 * \sa prime_table_get_index
 */
bool is_prime_brute (const unsigned int a);


/**
 * \brief Checks if a number is a prime by checking the supplied table.
 *
 * Search for a in table with binary search.
 *
 * \param a The number which primeness is checked.
 * \param primes The array of primes in ascending order.
 * \param psize The length of the prime array.
 * \return false if a was not found, true if it was.
 */
bool is_prime_table (const unsigned int a, const unsigned int *primes, const size_t psize);


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
int prime_table_get_index (const unsigned int a, const unsigned int *table, const size_t len);


/**
 * \brief Gives an upper limit of how much primes there are below n.
 * \param n The upper limit.
 * \return The upper limit of number of primes below n.
 */
unsigned int primes_under (const unsigned int n);


/**
 * \brief Get an array of n first primes.
 * \param n The number of primes to get.
 * \param primes At least n elements long pre-allocated array of integers.
 * \return The filled primes array or NULL if request failed (not enough memory).
 */
unsigned int *prime_table (const unsigned int n, unsigned int *primes);


/**
 * \brief Get size-long sieve of Erathosthenes (a prime sieve).
 *
 * \param sieve Size-long, preallocated bool array.
 * \param size The size of the sieve.
 * \return Total number of primes in the sieve.
 */
unsigned int prime_sieve (bool *sieve, const size_t size);


/**
 * \brief Get prime numbers from a sieve.
 *
 * Fills primes with at most psize primes, less if sieve doesn't have that many
 * primes.
 *
 * \param sieve Sieve containing the primes.
 * \param ssize Size (length) of the sieve.
 * \param primes Pre-allocated array of psize length.
 * \param psize Size of primes array.
 * \return Number of primes stored in prmies array.
 */
unsigned int get_primes_from_sieve (const bool *sieve, const size_t ssize,
                                    unsigned int *primes, const size_t psize);


/**
 * \brief Calculate nth permutation for int array.
 * \param data Int array holding the data.
 * \param size Number of elements in data array.
 * \param n Which permutation to calculate. NOTE: Must be greater than 0.
 */
int *nth_permutation (int *data, size_t size, unsigned int n);


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
unsigned int phi_recursive (unsigned int *phis, const size_t phis_len,
                            const bool *sieve, const size_t sieve_len,
                            const unsigned int x);


void init_pascal (size_t *result, size_t row_length);
size_t lower_bound (size_t *pascal, size_t row_length, size_t L, unsigned int n);
size_t upper_bound (size_t *pascal, size_t row_length, size_t L, unsigned int n);
size_t combination_size (size_t *pascal, size_t row_length, size_t L, size_t N);
void nth_combination (size_t *pascal, size_t row_length, int *base, size_t base_size,
                      size_t N, int *result, size_t result_size);



#endif /* HUTIL_H */

