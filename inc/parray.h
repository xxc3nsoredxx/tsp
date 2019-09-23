#ifndef PARRAY_H_20190922_010640
#define PARRAY_H_20190922_010640

struct parray_element_s {
    struct point_s point;
    struct parray_element_s *next;
};

struct parray_s {
    size_t len;
    struct parray_element_s *head;
    struct parray_element_s *tail;
};

struct parray_s* parray_init ();

void parray_push (struct parray_s *a, struct point_s p);

void parray_add (struct parray_s *a, unsigned int i, struct point_s p);

struct point_s parray_get (struct parray_s *a, unsigned int i);

struct point_s parray_remove (struct parray_s *a, unsigned int i);

void parray_remove_point (struct parray_s *a, struct point_s p);

void parray_print (struct parray_s *a);

void parray_delete (struct parray_s *a);

#endif /* PARRAY_H_20190922_010640 */
