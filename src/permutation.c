/* Copyright 2011 Sami Hyvönen
 * Licensed under the 2-clause BSD license. */

#include <stdlib.h>
#include <string.h>
#include "hutil.h"


static void init_factorial (unsigned int *fact, size_t size);
static void swip(int *data, const unsigned int I, const unsigned int J);


static void init_factorial (unsigned int *fact, size_t size) {
    unsigned int i;

    fact[0] = 1;

    for (i=1; i<size; i++)
        fact[i] = fact[i-1] * i;
}


/* Take integer from position J, move elements from I to J-1 one position
 * forward, and put original element J to position I. */
static void swip(int *data, const unsigned int i, const unsigned int j) {
    int tmp = data[j];

    memmove(data+i+1, data+i, (j-i) * sizeof(int));

    data[i] = tmp;
}


/* n > 0 */
/* TODO: check that factor size doesn't overflow */
int *nth_permutation (int *data, size_t size, unsigned int n) {
    unsigned int i = 0;
    unsigned int j;
    unsigned int f;
    unsigned int *factorial = malloc(size * sizeof(int));
    init_factorial(factorial, size);

    if (n==0)
        return NULL;

    n = n-1;

    while (n>0) {
        f = factorial[size-(i+1)];
        j = n / f;

        if (0 != j)
            swip(data, i, i+j);
        
        n = n % f;
        i++;
    }

    free(factorial);

    return data;
}


