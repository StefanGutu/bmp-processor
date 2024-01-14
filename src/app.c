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

    app_entry_point(argv[1], argv[2]);
    
    return EXIT_SUCCESS;
}
