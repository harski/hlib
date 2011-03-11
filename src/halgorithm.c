
#include "halgorithm.h"


int hBinSearch(int* arr, int len, int n) {
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

