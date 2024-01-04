#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

struct __attribute__((__packed__)) BITMAPHeader{ // bit_map_header_s _t
    char name[2]; // INFO: it's need to be BM
    unsigned int size;
    unsigned short int reserved1;
    unsigned short int reserved2;
    unsigned int image_offset; // from where image starts in file
};

/**
 * @brief 
 * 
 */
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

// typedef struct app_s {
//     struct Image *opened_image;
//     FILE* fp;
//     FILE* fbw;
//     navbar_t navbar_settings;
//     // uint32_t brush_color;
//     // uint32_t brush_size; // INFO: If drawing a line, then the width of the line should be the brush size
// } app_ptr_t, *app_t;

// typedef struct navbar_s {
//     uint32_t brush_color;
//     uint32_t brush_size;
// } navbar_t;

// typedef struct main_view_s {
//     struct Imgae *opened_image;
//     FILE* fbw;
// } main_view_t;

// typedef enum errors_s {
//     OK = 0,
//     COULD_NOT_OPEN_FILE = 1
// } errors_t;

int OpenBmpFile(FILE *fp);

// errors_t        init_application       (app_t * app);
// errors_t        open_image_file        (app_t app);
// errors_t        read_image             (app_t app);
// errors_t        write_image            (app_t app);
// errors_t        free_app               (app_t * app); // INFO: Calls free_image, and fclose on files;

struct mihai_s {
    int a, b, c;
};


#endif