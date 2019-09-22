#include <stdio.h>
#include <stdlib.h>

#include "fbg/screen.h"

unsigned int npoints = 0;
struct point_s *points = 0;

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
    points = calloc(npoints, sizeof(*points));
    for (cx = 0; cx < npoints; cx++) {
        unsigned int x = 0;
        unsigned int y = 0;

        fscanf(infile, " (%u,%u)", &x, &y);
        *(points + cx) = point(x, y);
    }

    /* Close infile since it is no longer needed */
    fclose(infile);

    printf("Numbr of points: %u\n", npoints);
    printf("Points:\n");
    for (cx = 0; cx < npoints; cx++) {
        printf("  (%u,%u)\n", (points + cx)->x, (points + cx)->y);
    }

    /* Clean up */
    free(points);

    return 0;
}
