
/* Front-end function to call for calculating gcd */
int h_gcd(int a, int b);


/* Function that does the dirty work for calculating
 * gcd
 */
static int h_calc_gcd(int *a, int *b);


/* Calculates the distinct prime factors of a number
 * num is the number to factorize
 * *res is the result array
 * returns the length of the result array
 */
int h_distinct_prime_factors(int num, int *res, int *table);


/* Returns 1 if a is prime, 0 if it's not */
int h_is_prime_brute(int a);


/* Returns a table of n first primes
 * n is the number of primes to get
 * primes is the preallocated table of integers
 */
int* h_prime_table(int n, int *primes);

