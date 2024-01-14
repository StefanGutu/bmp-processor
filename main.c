#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
int main(){

    //you can change it with your bmp
    char *file_name_source = "nature-photography-pictures.bmp";
    //the output file will be named new.bmp if you dont change it
    char *file_name_out = "new.bmp";

    FILE *fp_in = fopen(file_name_source,"rb");

    open_bmp_file(fp_in,file_name_out);
    return 0;
}