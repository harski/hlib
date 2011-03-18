#include <stdio.h>
#include "hutil.h"

int main(int argc, char** argv) {
    h_array *arr = h_array_create(sizeof(int));
    unsigned i;
    int d;
    
    for( i=1; i<32; i++) {
	d = (int)i;
	h_array_add(arr, &d);
    }

    for(i=0; i <32; i++) {
	printf("%d\n", *(int*)h_array_get_element(arr, i));
    }

    h_array_destroy(arr);
    return 0;
}

