struct h_pf {
    int *factors;
    int factor_count;
    int size;
};

struct h_pf *h_pf_create();
int h_pf_destroy(struct h_pf *st);
int h_pf_add_factor(struct h_pf *res, int num);
int h_pf_compress(struct h_pf *st);

