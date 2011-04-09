#include <stdlib.h>
#include "halgorithm.h"

/*******************************************
 * Binary search
 ******************************************/

int h_bin_search(int* arr, int len, int n) {
	int start = 0;
	int end = len;
	int middle = 0;

	/* Just do it! */
	while(start != end) {
		middle = (start+end) / 2;
		if ( arr[middle] == n ) {
			return middle;
		}
		if ( n < middle ) {
		  end = middle;
		} else {
		  start = middle;
		}
	}

	/* If the last index checked is the one */
	if ( arr[start] == n ) {
		return start;
	}

	/* Value not found */
	return -1;
}


/*******************************************
 * Permutation, originally by Sami Hyvonen
 ******************************************/

static unsigned int* init_factorial(const unsigned int size);
static void swip(int *data, const unsigned int L, const unsigned int I, const unsigned int J);

// 0 < size 
static unsigned int* init_factorial( const unsigned int size ) {
    unsigned int* fact = (unsigned *)malloc(sizeof(int)*size);
    fact[0] = 1;
    unsigned int i;
    for (i=1; i<size; i++) {
	fact[i] = fact[i-1] * i;
    }
    return fact;
}

// I < J <= L
static void swip(int data[], const unsigned int L, const unsigned int I, const unsigned int J) {
    int t = data[I];
    data[I] = data[J];
    int k;
    int i;
    for (i = I+1; i<=J; i++){
	k = data[i];
	data[i] = t;
	t = k;
    }
}

int* permutation(int data[], const unsigned int L , const unsigned int N) {
    unsigned int n = N-1;
    unsigned int i = 0;
    unsigned int j;
    unsigned int f;
    unsigned int* factorial = init_factorial(L);

    while (n>0)
    {
	f = factorial[L-(i+1)];
	j = n / f;
	if (0 != j) swip(data, L, i, i+j);
	n = n % f;
	i++;
    }
    return data;
}

