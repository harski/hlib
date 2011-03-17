#include <stdlib.h>
#include "h_pf.h"
#include "halgorithm.h"

struct h_pf *h_pf_create() {
    struct h_pf *pf = malloc(sizeof(struct h_pf));
    pf->size = 20;
    pf->factors = malloc(pf->size*sizeof(int));

    return pf;
}


int h_pf_destroy(struct h_pf *st) {
    free(st->factors);
    free(st);
    return 0;
}

int h_pf_add_factor(struct h_pf *res, int num) {
    if(res->size == res->factor_count) {
	/* new arrray of twice the size */
	int *tmp = malloc( 2*res->size*sizeof(int) );
	/* copy data */
	int i;
	for( i=0; i < res->factor_count; i++ ) {
	    tmp[i] = res->factors[i];
	}
	free(res->factors);
	res->factors = tmp;
	res->size *=2;
    }

    res->factors[res->factor_count++];

    return 0;
}

int h_pf_add_unique(struct h_pf *pf, int num) {
    /* if not there already, add */
    if( h_bin_search(pf->factors, pf->factor_count, num) == -1) {
	h_pf_add_factor(pf, num);
	return 1;
    }
    return -1;
}

int h_pf_compress(struct h_pf *st) {

    return 0;
}


