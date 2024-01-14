#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

void usage() {
    fprintf(stderr, "Usage: sbmp3 [file input.bmp] [file output.bmp]\n");
}

int main(int argc, char **argv) {

    if (argc != 3) {
        usage();
        exit(EXIT_FAILURE);
    }

    FILE *fp_in = fopen(argv[1],"rb");

    open_bmp_file(fp_in,argv[2]);
    return EXIT_SUCCESS;
}