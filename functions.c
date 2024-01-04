#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


void free_image(image_t *pic){
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


void write_image(image_t *pic){

    FILE *fbw = fopen("new.bmp", "wb");
    if (fbw == NULL) {
        perror("Error opening file");
        return; 
    }


    fwrite(&pic->infoBITMAP, sizeof pic->infoBITMAP, 1, fbw);

    fwrite(&pic->infoDIB, sizeof(dib_header_t), 1, fbw);

    int32_t padding = (4 - ((sizeof(rgb_t) * pic->infoDIB.width) % 4)) % 4;
    uint8_t pad_byte = 0;
    
    for (uint32_t i = 0; i < pic->infoDIB.height; i++) {
        fwrite(pic->rgb[i], sizeof (rgb_t), pic->infoDIB.width, fbw);

        fwrite(&pad_byte, 1, padding, fbw);
    }

    fclose(fbw);
}




void read_image(FILE *fp,image_t *pic) {
    if ((pic->rgb = (rgb_t **)malloc(pic->infoDIB.height * sizeof(rgb_t *))) == NULL) {
        printf("Error allocating memory for rows\n");
        exit(EXIT_FAILURE);
    }

    
    for (uint32_t i = 0; i < pic->infoDIB.height; i++) {
        if ((pic->rgb[i] = (rgb_t *)malloc(pic->infoDIB.width * sizeof(rgb_t))) == NULL) {
            printf("Error allocating memory for columns\n");
            exit(EXIT_FAILURE);
        }
    }

    int32_t padding = (4 - ((sizeof(rgb_t) * pic->infoDIB.width) % 4)) % 4;

    
    for (uint32_t i = 0; i < pic->infoDIB.height; i++) {
        if (fread(pic->rgb[i], sizeof(rgb_t), pic->infoDIB.width, fp) < pic->infoDIB.width) {
            fclose(fp);
            return;
        }
        
        fseek(fp, padding, SEEK_CUR);
    }
}

void open_bmp_file(FILE *fp){
 
    image_t *picture = NULL;

    if((picture=malloc(sizeof *picture)) == NULL){
        printf("Error memmory allocation for picture\n");
        exit(EXIT_FAILURE);
    }

    fread(&picture->infoBITMAP, sizeof picture->infoBITMAP, 1, fp);
    
    if(picture->infoBITMAP.name[0] != 'B' || picture->infoBITMAP.name[1] != 'M') {
        fclose(fp);
        return;
    }

    fread(&picture->infoDIB, sizeof picture->infoDIB,1,fp);
    
    if(picture->infoDIB.header_size != 40 || picture->infoDIB.compression != 0 || picture->infoDIB.bitsperpixel != 24) {
        fclose(fp);
        return;
    }

    fseek(fp,picture->infoBITMAP.image_offset,SEEK_SET);
    
    read_image(fp,picture);
    general_functions(picture);
    free_image(picture);

    fclose(fp);
} 
