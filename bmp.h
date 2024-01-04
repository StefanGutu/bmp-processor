#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct __attribute__((__packed__)) bit_map_header{ // bit_map_header_s _t
    char        name[2]; // INFO: it's need to be BM
    uint32_t    size;
    uint16_t    reserved1;
    uint16_t    reserved2;
    uint32_t    image_offset; // from where image starts in file
}bit_map_header_t;

typedef struct __attribute__((__packed__)) dib_header{
    uint32_t    header_size;
    uint32_t    width;
    uint32_t    height;
    uint16_t    colorplanes;
    uint16_t    bitsperpixel;
    uint32_t    compression;
    uint32_t    image_size;
    int32_t     bi_xpels_per_meter;
    int32_t     bi_ypels_per_meter;
    uint32_t    bi_clr_used;
    uint32_t    bi_clr_important;
}dib_header_t;

typedef struct __attribute__((__packed__)) rgb{
    uint8_t     red;
    uint8_t     green;
    uint8_t     blue;
}rgb_t; 

typedef struct image{
    bit_map_header_t    infoBITMAP;
    dib_header_t        infoDIB;
    rgb_t               **rgb;
}image_t;

typedef struct brush{
    rgb_t       brush_color;
    uint16_t    brush_size;
} brush_t;

typedef struct app{
    image_t         *opened_image;
    brush_t         brush_settings;
}app_t;


// INFO: if you want to change something andd to add new things you can use this 
// typedef struct main_view_s {
//     struct Imgae *opened_image;
//     FILE* fbw;
// } main_view_t;

// typedef enum errors_s {
//     OK = 0,
//     COULD_NOT_OPEN_FILE = 1
// } errors_t;

void     open_bmp_file          (FILE *fp);
void     read_image             (FILE *fp,app_t *newEdit);
void     write_image            (app_t *newEdit);// INFO: the information of the edited image will always be saved in new.bmp
void     free_image             (app_t *newEdit);// use this to free the memmory for the image
void     general_functions      (app_t *newEdit);//INFO: here are all the function to edit the image 


#endif