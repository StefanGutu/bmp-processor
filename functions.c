#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


void freeImage(struct Image *pic){
    if (pic != NULL) {
        if (pic->rgb != NULL) {
            for (uint32_t i = 0; i < pic->infoDIB.height; ++i) {
                if (pic->rgb[i] != NULL)
                    free(pic->rgb[i]);
            }

            free(pic->rgb);
        }

        free(pic);
    }
}


void writeImage(struct Image *pic){

    FILE *fbw = fopen("new1.bmp", "wb");
    if (fbw == NULL) {
        perror("Error opening file");
        return; 
    }


    fwrite(&pic->infoBITMAP, sizeof pic->infoBITMAP, 1, fbw);
    // fwrite(pic->infoBITMAP.name, 2, 1, fbw);
    // fwrite(&pic->infoBITMAP.size, sizeof(int), 1, fbw);
    // fwrite(&pic->infoBITMAP.reserved1, sizeof(unsigned short int), 1, fbw);
    // fwrite(&pic->infoBITMAP.reserved2, sizeof(unsigned short int), 1, fbw);
    // fwrite(&pic->infoBITMAP.image_offset, sizeof(unsigned int), 1, fbw);
    fwrite(&pic->infoDIB, sizeof(struct DIBHeader), 1, fbw);

    int32_t padding = (4 - ((sizeof(struct RGB) * pic->infoDIB.width) % 4)) % 4;
    uint8_t pad_byte = 0;
    
    for (uint32_t i = 0; i < pic->infoDIB.height; i++) {
        fwrite(pic->rgb[i], sizeof (struct RGB), pic->infoDIB.width, fbw);

        fwrite(&pad_byte, 1, padding, fbw);
    }

    fclose(fbw);
}




void readImage(FILE *fp, struct Image *pic) {
    if ((pic->rgb = (struct RGB **)malloc(pic->infoDIB.height * sizeof(struct RGB *))) == NULL) {
        printf("Error allocating memory for rows\n");
        exit(EXIT_FAILURE);
    }

    
    for (uint32_t i = 0; i < pic->infoDIB.height; i++) {
        if ((pic->rgb[i] = (struct RGB *)malloc(pic->infoDIB.width * sizeof(struct RGB))) == NULL) {
            printf("Error allocating memory for columns\n");
            exit(EXIT_FAILURE);
        }
    }

    int32_t padding = (4 - ((sizeof(struct RGB) * pic->infoDIB.width) % 4)) % 4;

    
    for (uint32_t i = 0; i < pic->infoDIB.height; i++) {
        if (fread(pic->rgb[i], sizeof(struct RGB), pic->infoDIB.width, fp) < pic->infoDIB.width) {
            fclose(fp);
            return;
        }
        
        fseek(fp, padding, SEEK_CUR);
    }
}

int OpenBmpFile(FILE *fp){
 
    struct Image *picture = NULL;

    if((picture=malloc(sizeof *picture)) == NULL){
        printf("Error memmory allocation for picture\n");
        exit(EXIT_FAILURE);
    }

    fread(&picture->infoBITMAP, sizeof picture->infoBITMAP, 1, fp);
    
    if(picture->infoBITMAP.name[0] != 'B' || picture->infoBITMAP.name[1] != 'M') {
        fclose(fp);
        return 1;
    }

    fread(&picture->infoDIB, sizeof picture->infoDIB,1,fp);
    
    if(picture->infoDIB.header_size != 40 || picture->infoDIB.compression != 0 || picture->infoDIB.bitsperpixel != 24) {
        fclose(fp);
        return 1;
    }

    printf("OFFSET: %u\n", picture->infoBITMAP.image_offset);
    
    // struct DIBHeader* temp = &picture->infoDIB;
    // printf("Header: %u\n", temp->header_size);
    // printf("Width: %u\n", temp->width);
    // printf("Height: %u\n", temp->height);
    // printf("Planes: %hu\n", temp->colorplanes);
    // printf("BitPerPixl: %hu\n", temp->bitsperpixel);
    // printf("Compress: %u\n", temp->compression);
    // printf("ImageSize: %u\n", temp->image_size);
    
    fseek(fp,picture->infoBITMAP.image_offset,SEEK_SET);
    
    readImage(fp,picture);
    writeImage(picture);

    
    freeImage(picture);

    fclose(fp);
    return 0;
} 
