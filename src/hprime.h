#include "h_pf.h"
#include "h_pl.h"

/* Front-end function to call for calculating gcd */
int h_gcd(int a, int b);


/* Function that does the dirty work for calculating
 * gcd
 */
static int h_calc_gcd(int *a, int *b);


/* Calculates the distinct prime factors of a number
 * num is the number to factorize
 * *pf is the prime factor struct
 * *pl is the prime struct
 * returns prime factor struct pointer
 */
struct h_pf *h_distinct_prime_factors(int num, struct h_pf *pf, struct h_pl *pl);


/* Returns 1 if a is prime, 0 if it's not */
int h_is_prime_brute(int a);


/* Returns a table of n first primes
 * n is the number of primes to get
 * primes is the preallocated table of integers
 */
int* h_prime_table(int n, int *primes);


/* Fills the struct with n first primes */
struct h_pl *h_prime_table_s(int n, struct h_pl *pl);

