#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

struct __attribute__((__packed__)) BITMAPHeader{
    char name[2]; // INFO: it's need to be BM
    unsigned int size;
    unsigned short int reserved1;
    unsigned short int reserved2;
    unsigned int image_offset; // from where image starts in file
};

struct __attribute__((__packed__)) DIBHeader{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short int colorplanes;
    unsigned short int bitsperpixel;
    unsigned int compression;
    unsigned int image_size;
    int32_t     bi_xpels_per_meter;
    int32_t     bi_ypels_per_meter;
    uint32_t    bi_clr_used;
    uint32_t    bi_clr_important;
};

// MAtrice
// bgrbgrrgbrgbrgb ... rgbpadding


struct __attribute__((__packed__)) RGB{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}; 

struct Image{
    struct BITMAPHeader infoBITMAP;
    struct DIBHeader infoDIB;
    struct RGB **rgb;
};

int OpenBmpFile(FILE *fp);


#endif