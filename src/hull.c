#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fbg/screen.h"

#include "hull.h"
#include "parray.h"

/* Compare two points based on the angle with x-axis */
int pcmp (struct point_s p0, struct point_s p1, struct point_s p2) {
    int m1n;
    int m1d;
    int m2n;
    int m2d;
    int m1norm;
    int m2norm;

    /* Calculate slopes (independent dy and dx) */
    m1n = p1.y - p0.y;
    m1d = p1.x - p0.x;
    m2n = p2.y - p0.y;
    m2d = p2.x - p0.x;

    /* Cross multiply */
    m1norm = m1n * m2d;
    m2norm = m2n * m1d;

    /* Return the comparison */
    /* printf("(%u,%u) (%u,%u) ", p1.x, p1.y, p2.x, p2.y); */
    if (m1norm < m2norm) {
        /* printf("<\n"); */
        return -1;
    } else if (m1norm > m2norm) {
        /* printf(">\n"); */
        return 1;
    } else {
        /* printf("=\n"); */
        return 0;
    }
}

/* Sort an array of point_s by the angle with the x-axis */
struct point_s* sort (struct point_s p0, struct point_s *a, size_t len) {
    struct point_s *ret = calloc(len, sizeof(*ret));
    unsigned int i;
    unsigned int j;

    memcpy(ret, a, len * sizeof(*a));

    /* TODO: implement a better sort than insertion sort */
    for (i = 1; i < len; i++) {
        for (j = i; j > 0 && pcmp(p0, *(ret + (j - 1)), *(ret + j)) > 0; j--) {
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

/* Calculate the the cross product of three points
 *  =0: colinear
 *  >0: left turn
 *  <0: right turn
 */
int pcross (struct point_s p1, struct point_s p2, struct point_s p3) {
    int ret = 0;

    ret = (p2.x - p1.x) * (p3.y - p1.y);
    ret -= (p2.y - p1.y) * (p3.x - p1.x);

    return ret;
}

/* Calculate a convex hull from a parray */
struct parray_s *calc_hull (struct parray_s *a) {
    struct parray_s *ret = parray_init();
    struct parray_s *a2 = parray_copy(a);
    struct point_s *points = parray_to_array(a);
    struct point_s *sorted;
    struct point_s p0 = point(UINT_MAX, UINT_MAX);
    unsigned int cx;

    /* Use Graham Scan algorithm for the convex hull */
    /* Calculate P0 (leftmost point with lowest y coordinate) */
    for (cx = 0; cx < a->len; cx++) {
        if ((points + cx)->y < p0.y) {
            p0 = *(points + cx);
        } else if ((points + cx)->y == p0.y && (points + cx)->x < p0.x) {
            p0 = *(points + cx);
        }
    }
    /* printf("P0: (%u,%u)\n", p0.x, p0.y); */
    parray_remove_point(a2, p0);
    free(points);
    points = parray_to_array(a2);

    /* Sort points based on P0 */
    sorted = sort(p0, points, a2->len);
    /*
    printf("Sorted points:\n");
    for (cx = 0; cx < a2->len; cx++) {
        printf("(%u,%u)\n", (sorted + cx)->x, (sorted + cx)->y);
    }
    */

    /* Scan through all the points */
    for (cx = 0; cx < a2->len; cx++) {
        struct point_s cur = *(sorted + cx);
        struct point_s top = parray_get(ret, ret->len - 1);
        struct point_s next_top = parray_get(ret, ret->len - 2);
        while (ret->len > 1 && pcross(next_top, top, cur) < 0) {
            parray_remove(ret, ret->len - 1);
            top = parray_get(ret, ret->len - 1);
            next_top = parray_get(ret, ret->len - 2);
        }
        parray_push(ret, cur);
    }

    /* Prepend the initial point */
    parray_add(ret, 0, p0);

    free(sorted);
    free(points);
    parray_delete(a2);
    return ret;
}
