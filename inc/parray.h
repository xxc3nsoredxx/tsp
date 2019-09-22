#ifndef PARRAY_H_20190922_010640
#define PARRAY_H_20190922_010640

struct parray_s {
    struct point_s point;
    struct parray_s *next;
};

struct parray_s* push (struct parray_s *a, struct point_s p);

void parray_delete (struct parray_s *a);

void parray_print (struct parray_s *a);

#endif /* PARRAY_H_20190922_010640 */
