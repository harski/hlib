#ifndef HALGORITHM_H
#define HALGORITHM_H

/*******************************************
 * Binary search
 ******************************************/

/* Use binary search to the int array
 * arr is the array where the num is serched
 * len is the length of the array
 * n is the number to be searched
 * if n is not found, -1 is returned
 * otherwise index of the target is returned
 */
int h_bin_search(int* arr, int len, int n);


/*******************************************
 * Permutation, originally by Sami Hyvonen
 ******************************************/

int* permutation(int *data, const unsigned int L, const unsigned int N);


#endif /* HALGORITHM_H */

