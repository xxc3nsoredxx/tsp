#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fbg/screen.h"

#include "hull.h"
#include "parray.h"

/* Compare two points based on the angle with x-axis */
int pcmp (struct point_s p1, struct point_s p2) {
    double m1;
    double m2;

    /* Calculate slopes */
    if (p1.x == 0) {
        m1 = DBL_MAX;
    } else if (p1.y == 0) {
        m1 = 0.0;
    } else {
        m1 = (double)p1.y / p1.x;
    }
    if (p2.x == 0) {
        m2 = DBL_MAX;
    } else if (p2.y == 0) {
        m2 = 0.0;
    } else {
        m2 = (double)p2.y / p2.x;
    }

    /* TODO: Possibly fix later -------- */
    if (m1 < m2) {
        return -1;
    } else if (m1 > m2) {
        return 1;
    } else {
        return 0;
    }
    /* --------------------------------- */
}

/* Sort an array of point_s by the angle with the x-axis */
struct point_s* sort (struct point_s *a, size_t len) {
    struct point_s *ret = calloc(len, sizeof(*ret));
    unsigned int i;
    unsigned int j;

    memcpy(ret, a, len * sizeof(*a));

    /* TODO: implement a better sort than insertion sort */
    for (i = 1; i < len; i++) {
        for (j = i; j > 0 && pcmp(*(ret + (j - 1)), *(ret + j)) > 0; j--) {
            (ret + j)->x ^= (ret + (j - 1))->x;
            (ret + (j - 1))->x ^= (ret + j)->x;
            (ret + j)->x ^= (ret + (j - 1))->x;

            (ret + j)->y ^= (ret + (j - 1))->y;
            (ret + (j - 1))->y ^= (ret + j)->y;
            (ret + j)->y ^= (ret + (j - 1))->y;
        }
    }

    return ret;
}

/* Calculate a convex hull from a parray */
struct parray_s *calc_hull (struct parray_s *a) {
    struct parray_s *ret = parray_init();
    struct point_s *points = parray_to_array(a);
    struct point_s *sorted = sort(points, a->len);
    unsigned int cx;

    printf("Sorted points:\n");
    for (cx = 0; cx < a->len; cx++) {
        printf("(%u,%u)\n", (sorted + cx)->x, (sorted + cx)->y);
    }

    free(sorted);
    free(points);
    return ret;
}
