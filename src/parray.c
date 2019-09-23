#include <stdio.h>
#include <stdlib.h>

#include "fbg/screen.h"

#include "parray.h"

/* Initialize a parray_s */
struct parray_s* parray_init () {
    struct parray_s *ret = 0;

    ret = calloc(1, sizeof(*ret));

    return ret;
}

/* Push an element onto the end */
void parray_push (struct parray_s *a, struct point_s p) {
    struct parray_element_s *add = calloc(1, sizeof(*add));

    add->point = p;

    /* Empty array */
    if (!a->head) {
        a->head = add;
        a->tail = add;
    } else {
        a->tail->next = add;
        a->tail = add;
    }

    a->len++;
}

/* Add a point before element i */
void parray_add (struct parray_s *a, unsigned int i, struct point_s p) {
    unsigned int cx;
    struct parray_element_s *prev;
    struct parray_element_s *cur;
    struct parray_element_s *add;

    /* Out of bounds */
    if (i >= a->len) {
        return;
    }

    add = calloc(1, sizeof(*add));
    add->point = p;

    /* First element */
    if (i == 0) {
        add->next = a->head;
        a->head = add;
        a->len++;
        return;
    }

    /* Go to the right position */
    prev = a->head;
    cur = prev->next;
    for (cx = 1; cx < i; cx++) {
        prev = cur;
        cur = prev->next;
    }

    /* Inject the new point */
    prev->next = add;
    add->next = cur;
    a->len++;
}

/* Get the point at element i */
struct point_s parray_get (struct parray_s *a, unsigned int i) {
    unsigned int cx;
    struct parray_element_s *cur;

    for (cx = 0, cur = a->head; cx < i; cx++) {
        cur = cur->next;
    }

    return cur->point;
}

/* Get and remove the point at element i */
struct point_s parray_remove (struct parray_s *a, unsigned int i) {
    unsigned int cx;
    struct point_s ret;
    struct parray_element_s *prev;
    struct parray_element_s *cur;

    /* Out of bounds */
    if (i >= a->len) {
        return ret;
    }

    /* First element */
    if (i == 0) {
        cur = a->head;
        ret = cur->point;
        a->head = a->head->next;
        a->len--;

        /* Only element */
        if (a->len == 0) {
            a->tail = 0;
        }

        free(cur);

        return ret;
    }

    /* Go to the right position */
    prev = a->head;
    cur = prev->next;
    for (cx = 1; cx < i; cx++) {
        prev = cur;
        cur = prev->next;
    }

    /* Extract the point */
    ret = cur->point;
    prev->next = cur->next;
    free(cur);
    a->len--;

    /* Last element */
    if (i == a->len) {
        a->tail = prev;
    }

    return ret;
}

/* Print the contents of a parray_s */
void parray_print (struct parray_s *a) {
    struct parray_element_s *cur = a->head;

    if (!cur) {
        printf("Empty Array\n");
    } else {
        do {
            printf("(%u, %u)\n", cur->point.x, cur->point.y);
            cur = cur->next;
        } while (cur);
    }
}

/* Free up the memory used by a parray_s */
void parray_delete (struct parray_s *a) {
    struct parray_element_s *old;
    struct parray_element_s *cur = a->head;

    while (cur) {
        old = cur;
        cur = cur->next;
        free(old);
    }

    free(a);
}
