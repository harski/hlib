#ifndef HPRIME_H
#define HPRIME_H

/* Upper limits for number of primes */
#define H_PRIMES_IN_UINT32 203280221
#define H_PRIMES_IN_INT32 105097565
#define H_PRIMES_IN_UINT64 18446744073709551616
#define H_PRIMES_IN_INT64 9223372036854775808


/* Front-end function to call for calculating gcd */
int h_gcd(int a, int b);


/* Returns 1 if a is prime, 0 if it's not */
int h_is_prime_brute(int a);


/* Checks if a given number is a prime by checking the table.
 * a is the number to be searched,
 * table is the array of primes,
 * len is the length of the prime table.
 * Returns a non-zero or 0 if depending wether the number was found.
 */
int h_is_prime_table(int a, int *table, int len);


/* Returns the index of the prime or -1 if it isn't in the table. */
int h_prime_table_get_index(int a, int *table, int len);

/* Returns the number of primes under n
 * *n is the upper limit
 */
int h_primes_under(int *n);


/* Returns a table of n first primes
 * n is the number of primes to get
 * primes is the preallocated table of integers
 */
int* h_prime_table(int n, int *primes);

#endif 

