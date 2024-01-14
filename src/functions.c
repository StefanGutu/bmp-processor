#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


void free_image(app_t *newEdit){
    if(newEdit != NULL){
        if (newEdit->opened_image != NULL) {
            if (newEdit->opened_image->rgb != NULL) {
                for (uint32_t i = 0; i < newEdit->opened_image->infoDIB.height; ++i) {
                    if (newEdit->opened_image->rgb[i] != NULL)
                        free(newEdit->opened_image->rgb[i]);
                }

                free(newEdit->opened_image->rgb);
            }

            free(newEdit->opened_image);
        }
    }
    free(newEdit);
}


void write_image(app_t *newEdit){

    FILE *fp = fopen(newEdit->file_name_out, "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return; 
    }


    fwrite(&newEdit->opened_image->infoBITMAP, sizeof newEdit->opened_image->infoBITMAP, 1, fp);

    fwrite(&newEdit->opened_image->infoDIB, sizeof(dib_header_t), 1, fp);

    int32_t padding = (4 - ((sizeof(rgb_t) * newEdit->opened_image->infoDIB.width) % 4)) % 4;
    uint8_t pad_byte = 0;
    
    for (uint32_t i = 0; i < newEdit->opened_image->infoDIB.height; i++) {
        fwrite(newEdit->opened_image->rgb[i], sizeof (rgb_t), newEdit->opened_image->infoDIB.width, fp);

        fwrite(&pad_byte, 1, padding,fp);
    }

    fclose(fp);
}




void read_image(FILE *fp,app_t *newEdit) {

    if ((newEdit->opened_image->rgb = (rgb_t **)malloc(newEdit->opened_image->infoDIB.height * sizeof(rgb_t *))) == NULL) {
        printf("Error allocating memory for rows\n");
        exit(EXIT_FAILURE);
    }

    
    for (uint32_t i = 0; i < newEdit->opened_image->infoDIB.height; i++) {
        if ((newEdit->opened_image->rgb[i] = (rgb_t *)malloc(newEdit->opened_image->infoDIB.width * sizeof(rgb_t))) == NULL) {
            printf("Error allocating memory for columns\n");
            exit(EXIT_FAILURE);
        }
    }

    int32_t padding = (4 - ((sizeof(rgb_t) * newEdit->opened_image->infoDIB.width) % 4)) % 4;

    
    for (uint32_t i = 0; i < newEdit->opened_image->infoDIB.height; i++) {
        if (fread(newEdit->opened_image->rgb[i], sizeof(rgb_t), newEdit->opened_image->infoDIB.width, fp) < newEdit->opened_image->infoDIB.width) {
            fclose(fp);
            return;
        }
        
        fseek(fp, padding, SEEK_CUR);
    }
}

void open_bmp_file(FILE *fp,char *file_name){
    app_t *newEdit = NULL;

    if((newEdit=malloc(sizeof *newEdit)) == NULL){
        printf("Error memmory allocation for picture\n");
        exit(EXIT_FAILURE);
    }

    

    if((newEdit->opened_image=malloc(sizeof * (newEdit->opened_image))) == NULL){
        printf("Error memmory allocation for picture\n");
        exit(EXIT_FAILURE);
    }

    fread(&newEdit->opened_image->infoBITMAP, sizeof(newEdit->opened_image->infoBITMAP), 1, fp);
    
    if(newEdit->opened_image->infoBITMAP.name[0] != 'B' || newEdit->opened_image->infoBITMAP.name[1] != 'M') {
        fclose(fp);
        return;
    }

    fread(&newEdit->opened_image->infoDIB, sizeof newEdit->opened_image->infoDIB,1,fp);
    
    if(newEdit->opened_image->infoDIB.header_size != 40 || newEdit->opened_image->infoDIB.compression != 0 || newEdit->opened_image->infoDIB.bitsperpixel != 24) {
        fclose(fp);
        return;
    }

    fseek(fp,newEdit->opened_image->infoBITMAP.image_offset,SEEK_SET);
    
    read_image(fp,newEdit);
    
    newEdit->file_name_out = file_name;

    general_functions(newEdit);
    free_image(newEdit);

    fclose(fp);
} 
