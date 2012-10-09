/* Copyright 2012 Sami Hyvönen
 * Licensed under the 2-clause BSD license. */

#include <stdlib.h>
#include "hutil.h"

/*
Usage: 
Base array base = {1,2,3,4,5}, length L = |B| = 5.
Init_pascal(K), where K > L.
Use lower_bound(pascal,K,L,s1) for initialize n to |result| = s1.
Use upper_bound(pascal,K,L,s2) for finalize n to |result| = s2.
Malloc result array of length s in two cases:
1. s1 == s2 then s = s1 = s2, constant size, malloc and free result array
    outside of loop.
2. s1 < s2 then s = combination_size(pascal,K,L,n), variable size, malloc and 
    free result array inside of loop.
Use nth_combination(pascal,K,base,L,n,result,s) for generate nth combination
from base array to result array of size s.

Tested: works up to number of system bits, 32 or 64.
Practical: Gets very slow on when L > 32. ( several minutes )
Hint: Split index space* for multicore for speedup.
*) upper_bound-lower_bound 
 */

/* time complexity O(n^2), where n = row_length.
 * result is row_length * row_length array. */
void init_pascal (size_t *result, size_t row_length)
{
    unsigned int i, j;

    result[0] = 1;
    
    for (i=1; i<row_length; ++i)
        result[i] = 2*result[i-1];

	for (i=row_length; i<row_length*row_length; i += row_length) {
		for (j=0; j<row_length; ++j) {
			if (0 == j || i == row_length*j)
				result[i+j] = 1;
			else if (i > j*row_length)
			    result[i+j] = result[i-row_length+j-1]+result[i-row_length+j];
            else
                result[i+j] = result[i+j-1]+result[i-row_length+j-1];
		}
	}
}


/* 0 < n <= L, time complexity O(1) */
size_t lower_bound (size_t *pascal, size_t row_length, size_t L, unsigned int n)
{
    return pascal[(L-n+1)*row_length+L];
}


/* 0 < n <= L, time complexity O(1) */
size_t upper_bound (size_t *pascal, size_t row_length, size_t L, unsigned int n)
{
    return pascal[(L-n)*row_length+L];
}


/*time complexity O(log n), where n = row_length*/
size_t combination_size (size_t *pascal, size_t row_length, size_t L, size_t N)
{
    if ( N == 0 || pascal[L] <= N )
        return 0;

    size_t h = 0, l = L, mid = 0;

    do{
        mid = (h+l)/2;
        if (N < pascal[mid*row_length+L])
            h = mid+1;
        else if (pascal[mid*row_length+L] < N)
            l = mid;
        else
            h = l = mid;
    } while (h != l);

    return L-h+1;
}

/* pascal = init_pascal( K ), where L < K, L = |base|
time complexity O(n), where n = row_length.
*/
void nth_combination (size_t *pascal, size_t row_length,
                      int *base, size_t base_size,
                      size_t N, 
                      int *result, size_t result_size)
{
	size_t n = N-pascal[row_length*(base_size+1-result_size)+base_size];
	size_t k = 1;
	size_t m = 1;
	size_t h = 0;
    size_t r = (base_size-1)*row_length; // L-k

	while (h < result_size) {
		if (n < pascal[r+result_size-m]) {
			result[h] = base[k-1];
            ++h;
			++m;
		} else {
			n -= pascal[r+result_size-m];
		}

		++k;
        r -= row_length;
	}
}

