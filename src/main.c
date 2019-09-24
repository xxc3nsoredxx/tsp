#include <stdio.h>
#include <stdlib.h>

#include "fbg/screen.h"

#include "hull.h"
#include "parray.h"

unsigned int npoints = 0;
struct parray_s *points = 0;
struct parray_s **con_hulls = 0;
size_t nhulls = 0;

void usage () {
    printf("Usage:\n");
    printf("  tsp [file]\n");
    printf("  [file] is a file of the following format:\n");
    printf("    number of points\n");
    printf("    (x,y) with one point per line\n");
    printf("      x and y nonnegative integers");
}

int main (int argc, char **argv) {
    FILE *infile;
    unsigned int cx;

    /* Test commandline args */
    if (argc != 2) {
        usage();
        exit(-1);
    }

    /* Attempt to open file containing points */
    infile = fopen(*(argv + 1), "r");
    if (!infile) {
        printf("Unable to open file: %s\n", *(argv + 1));
        exit(-1);
    }

    /* Read the number of points */
    fscanf(infile, " %u", &npoints);

    /* Read the points into the array */
    points = parray_init();
    for (cx = 0; cx < npoints; cx++) {
        unsigned int x = 0;
        unsigned int y = 0;

        fscanf(infile, " (%u,%u)", &x, &y);
        parray_push(points, point(x, y));
    }

    /* Close infile since it is no longer needed */
    fclose(infile);

    printf("Read points\n");
    printf("===========\n");
    printf("Numbr of points: %u\n", npoints);
    printf("Points:\n");
    parray_print(points);

    while(points->len > 0) {
        struct parray_s *hull = 0;
        /* Allocate space for a new convex hull */
        nhulls++;
        con_hulls = realloc(con_hulls, nhulls * sizeof(*con_hulls));

        /* Calcuate a convex hull */
        hull = calc_hull(points);
        printf("\n");
        printf("Convex hull\n");
        printf("===========\n");
        printf("Convex hull size: %lu\n", hull->len);
        printf("Points:\n");
        parray_print(hull);

        /* Remove the convex hull from the list of points */
        for (cx = 0; cx < hull->len; cx++) {
            parray_remove_point(points, parray_get(hull, cx));
        }

        *(con_hulls + (nhulls - 1)) = hull;
    }

    /* Clean up */
    for (cx = 0; cx < nhulls; cx++) {
        parray_delete(*(con_hulls + cx));
    }
    free(con_hulls);
    parray_delete(points);

    return 0;
}
