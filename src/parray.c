#include <stdio.h>
#include <stdlib.h>

#include "fbg/screen.h"

#include "parray.h"

/* Initialize a parray_s with the given point */
struct parray_s* init (struct point_s p) {
    struct parray_s *ret = 0;

    ret = calloc(1, sizeof(*ret));
    ret->point = p;
    ret->next = 0;

    return ret;
}

/* Add a point to the head */
struct parray_s* push (struct parray_s *a, struct point_s p) {
    struct parray_s *added;

    added = init(p);
    added->next = a;

    return added;
}

/* Delete a parray_s */
void parray_delete (struct parray_s *a) {
    struct parray_s *old;
    struct parray_s *old_next;

    if (!a) {
        return;
    }

    old = a;
    old_next = old->next;

    while (old_next) {
        free(old);
        old = old_next;
        old_next = old->next;
    }

    free(old);
}

/* Print the contents of a parray_s */
void parray_print (struct parray_s *a) {
    struct parray_s *cur = a;

    if (!cur) {
        printf("Empty Array\n");
    } else {
        do {
            printf("(%u, %u)\n", cur->point.x, cur->point.y);
            cur = cur->next;
        } while (cur);
    }
}
