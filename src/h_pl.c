#include <stdlib.h>
#include "h_pl.h"

struct h_pl *h_pl_create() {
    struct h_pl *pl = malloc(sizeof(struct h_pl));
    pl->size = 20;
    pl->list = malloc(pl->size*sizeof(int));
    pl->head = 0;
}

int h_pl_destroy(struct h_pl *pl) {
    free(pl->list);
    free(pl);
    return 0;
}

int h_pl_add_prime(struct h_pl *pl, int a) {
    if( pl->head == pl->size ) {
	int* tmp = malloc(pl->size*2 * sizeof(int));
	int i;

	for( i=0; i< p->head; i++ ) {
	    tmp[i] = pl[i];
	}

	free(pl);
	pl = tmp;
    }

    pl->list[pl->head] = a;
    pl->head++;
    return 0;
}
