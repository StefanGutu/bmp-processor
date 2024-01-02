#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
//nature-photography-pictures
int main(){
    char *FileName = "nature-photography-pictures.bmp";
    FILE *fp = fopen(FileName,"rb");
    OpenBmpFile(fp);
    return 0;
}