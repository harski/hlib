#ifndef H_UTIL_H
#define H_UTIL_H


#define ARRAY_INIT_SPACE 32

typedef struct h_array h_array;
struct h_array {
    void *array;
    size_t element_size;
    unsigned size;
    unsigned elements;
};

h_array *h_array_create(size_t size);
int h_array_destroy(h_array *ha);
int h_array_add(h_array *ha, void *elem);
void* h_array_get_element(h_array *ha, unsigned index);

#endif /* H_UTIL_H */
