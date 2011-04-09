
/* Front-end function to call for calculating gcd */
int h_gcd(int a, int b);


/* Returns 1 if a is prime, 0 if it's not */
int h_is_prime_brute(int a);


/* Checks if a given number is a prime by checking the table.
 * a is the number to be searched,
 * table is the array of primes,
 * len is the length of the prime table.
 * Returns the index of the found value or -1 if value not found
 */
int h_is_prime_table(int *a, int *table, int *len);


/* Returns a table of n first primes
 * n is the number of primes to get
 * primes is the preallocated table of integers
 */
int* h_prime_table(int n, int *primes);

