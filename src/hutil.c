#include <stdlib.h>
#include <string.h>
#include "hutil.h"

static void* h_array_get_real_index(h_array *ha, unsigned pos) {
    return (void *) (ha->array + ( ha->element_size * pos));
}

h_array *h_array_create(size_t size) {
    h_array *arr = malloc(sizeof(h_array));
    arr->element_size = size;
    arr->size = ARRAY_INIT_SPACE;
    arr->elements = 0;
    arr->array = malloc(arr->size * arr->element_size);

    return arr;
}


int h_array_destroy(h_array *ha) {
    free(ha->array);
    free(ha);

    return 0;
}

int h_array_add(h_array *ha, void *elem) {
    if(ha->elements == ha->size) {
        void *tmp = malloc(2*ha->size*ha->element_size);

        /* Copy array */
        memcpy(tmp, ha->array, ha->elements * ha->element_size);
        
        free(ha->array);
        ha->array = tmp;
        ha->size *= 2;
    }

    /* Get index and copy the element */
    void *target = h_array_get_real_index(ha, ha->elements);
    memcpy(target, elem, ha->element_size);
    ha->elements++;
    return 0;
}

void* h_array_get_element(h_array *ha, unsigned index) {
    return h_array_get_real_index(ha, index);
}

