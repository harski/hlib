struct h_prime_list {
    int *list;
    int head;
    int size;
};

struct h_pl *h_pl_create();
int h_pl_destroy(struct h_pl *pl);
int h_pl_add_prime(struct h_pl *pl, int a);

