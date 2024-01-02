#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

void freeImage(struct Image *pic);
struct Image *readImage(FILE *fp,int width,int height);


unsigned char grayscale(struct RGB rgb){
    return ((0.3*rgb.red) + (0.6*rgb.green) + (0.1*rgb.blue));
}


// converts an RGB image in an Gray image
void RGBtoGray(struct Image pic){
    
    for(int i = 0; i < pic.height;i++){
        for(int j = 0;j < pic.width;j++){
            pic.rgb[i][j].red = grayscale(pic.rgb[i][j]);
            pic.rgb[i][j].green = grayscale(pic.rgb[i][j]);
            pic.rgb[i][j].blue = grayscale(pic.rgb[i][j]);
        }
    }
}

void createBWImage(struct BITMAPHeader header,struct DIBHeader dibheader,struct Image pic){
    
    FILE *fp = fopen("new.bmp","rb+");


    RGBtoGray(pic);

    fwrite(header.name,2,1,fp);
    fwrite(&header.size,3*sizeof(int),1,fp);

    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp);

    for(int i = pic.height-1;i >= 0;i--){
        fwrite(pic.rgb[i],((24 * pic.width + 31)/32)*4,1,fp);
    }
    
    fclose(fp);
}

//Make an image with TEXT
void imageToText(struct BITMAPHeader header,struct DIBHeader dibheader,struct Image pic){

    FILE *fp = fopen("new.bmp","rb+");
    

    char txtPixel[] = {'#','$','%','&','Q','Y','U','O'};
    unsigned char gs;

    for(int i = 0;i < pic.height;i++){
        for(int j = 0; j < pic.width;j++){
            gs = grayscale(pic.rgb[i][j]);
            printf("%c",txtPixel[gs/32]);
        }
        printf("\n");
    }

    
    fclose(fp);
}

//function to free the memmory of the image that was allocated
void freeImage(struct Image *pic){
    for(int i = pic->height-1;i >= 0;i--){
        free(pic->rgb[i]);
    }
    free(pic->rgb);
    free(pic);
}


// function to read image data
struct Image *readImage(FILE *fp,int width,int height){
    struct Image *pic = NULL;
    
    if((pic = (struct Image*)malloc(sizeof(struct Image)))==NULL){
        printf("Image alloc\n");
        exit(EXIT_FAILURE);
    }

    if((pic->rgb = (struct RGB**)malloc(height*sizeof(void*)))==NULL){
        printf("Error allocating memmory for rgb\n");
        exit(EXIT_FAILURE);

    }
    pic->height = height;
    pic->width = width;
    int bytestoread = ((24 * width + 31)/32)*4;
    int numOfRGB = bytestoread/sizeof(struct RGB)+1;

    for(int i = height-1;i >= 0;i--){
        if((pic->rgb[i] = (struct RGB*)malloc(numOfRGB*sizeof(struct RGB))) == NULL){
            printf("Error allocating memmory for rgb\n");
            exit(EXIT_FAILURE);
        }
        fread(pic->rgb[i],1,bytestoread,fp);
    }

    return pic;
}

//function that make the pixel black for drawing
void paintBlack(struct RGB *pixel){
    struct RGB temp;
    temp.red = 0;
    temp.green = 0;
    temp.blue = 0;
    *pixel = temp;
}

void drawingLinesOnMatrix(struct Image pic){
    int x1,y1,x2,y2;
    printf("Enter the coordinates\n");
    printf("x1 y1 x2 y2:\n");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    
    if(y1 == y2){
        for(int i = 0; i < pic.height;i++){
            for(int j = 0;j < pic.width;j++){
                if(i == y1 && (((j>=x1) && (j<=x2))|| ((j<=x1) && (j>=x2)))){
                    paintBlack(&pic.rgb[i][j]);
                }
            }
        }
    }else if(x1 == x2){
        for(int i = 0; i < pic.height;i++){
            for(int j = 0;j < pic.width;j++){
                if(j == x1 && (((i>=y1) && (i<=y2))|| ((i<=y1) && (i>=y2)))){
                    paintBlack(&pic.rgb[i][j]);
                }
            }
        }
    }else{
        for(int i = 0; i < pic.height;i++){
            for(int j = 0;j < pic.width;j++){
                if((((j>=x1) && (j<=x2))|| ((j<=x1) && (j>=x2))) && (((i>=y1) && (i<=y2))|| ((i<=y1) && (i>=y2))) && (x1 == y1) && (i == j)){
                        paintBlack(&pic.rgb[i][j]);
                }else if((x1 == y2) && (i + j == pic.width - 1) &&  (((i>=y1) && (i<=y2))|| ((i<=y1) && (i>=y2)))){
                        paintBlack(&pic.rgb[i][j]);
                }
            }
        }
       
    }

}


// function that draw lines on the image
void drawLine(struct BITMAPHeader header,struct DIBHeader dibheader,struct Image pic){
    FILE *fp = fopen("new.bmp","rb+");
    
    drawingLinesOnMatrix(pic);

    fwrite(header.name,2,1,fp);
    fwrite(&header.size,3*sizeof(int),1,fp);

    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp);
    for (int i = pic.height - 1; i >= 0; i--) {
        fwrite(pic.rgb[i],((24 * pic.width + 31)/32)*4,1,fp);
    }


    
    fclose(fp);
}

void drawingSquareOnMatrix(struct Image pic){
    int x1,y1,x2,y2;
    printf("Enter the coordinates\n");
    printf("x1 y1 x2 y2:\n");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

    for(int i = 0;i<pic.height;i++){
        for(int j = 0;j<pic.width;j++){
            if(((i == y1) && (j >= x1 && j <=x2)) || ((i == y2) && (j >= x1 && j <=x2))  || ((j == x1) && (i > y1 && i < y2)) ||  ((j == x2) && (i > y1 && i < y2)) ){
                paintBlack(&pic.rgb[i][j]);
            }
        }
    }

}

//function that draws the square on the image
void drawSquare(struct BITMAPHeader header,struct DIBHeader dibheader,struct Image pic){
    FILE *fp = fopen("new.bmp","rb+");

    drawingSquareOnMatrix(pic);

    fwrite(header.name,2,1,fp);
    fwrite(&header.size,3*sizeof(int),1,fp);

    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp);
    for(int i = pic.height - 1;i>=0; i--){
        fwrite(pic.rgb[i],((24*pic.width+31)/32)*4,1,fp);
    }

    fclose(fp);
}

void drawingTraingleOnMatrix(struct Image pic){
    int x1,y1,x2,y2,x3;
    printf("Enter the coordinates\n");
    printf("x1 y1 x2 y2 x3:\n");
    scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&x3);
    
    int secondDiagonal = x1 + y1;

    for(int i = 0; i < pic.height;i++){
        for(int j = 0;j < pic.width;j++){
            if (i >= y1 && i <= y2 && ((j - x1) * (y2 - y1) == (i - y1) * (x3 - x1))) {
            paintBlack(&pic.rgb[i][j]);
        }
            if (j >= x2 && j <= x1 && i >= y1 && i <= y2 && secondDiagonal == i + j) {
                paintBlack(&pic.rgb[i][j]);
            }
            if (i == y2 && j >= x2 && j <= x3) {
                paintBlack(&pic.rgb[i][j]);
            }
                
        }
    }

}

//function that draws the triangle on the image
void drawTriangle(struct BITMAPHeader header,struct DIBHeader dibheader,struct Image pic){
    FILE *fp = fopen("new.bmp","rb+");

    drawingTraingleOnMatrix(pic);

    fwrite(header.name,2,1,fp);
    fwrite(&header.size,3*sizeof(int),1,fp);

    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp);
    for(int i = pic.height - 1;i>=0; i--){
        fwrite(pic.rgb[i],((24*pic.width+31)/32)*4,1,fp);
    }
    fclose(fp);

}


// function from where you can change the image
void generalFunctions(struct BITMAPHeader header,struct DIBHeader dibheader,struct Image pic){
    
    int num = 1;

    while(num != 0){
        printf("What do you want to change?\n");
        printf("0.Leave\n");
        printf("1.Make it gray\n");
        printf("2.Print the image in text (in terminal)\n");
        printf("3.Draw a line\n");
        printf("4.Draw a square\n");
        printf("5.Draw a triangle\n");
        scanf("%d",&num);

        if(num == 0)break;

        switch (num){
        case 1:
            createBWImage(header,dibheader,pic);
            break;
        case 2:
            imageToText(header,dibheader,pic);
            break;
        case 3:
            drawLine(header,dibheader,pic);
            break;
        case 4:
            drawSquare(header,dibheader,pic);
            break;
        case 5:
            drawTriangle(header,dibheader,pic);
            break;
        default:
            break;
        }
    }

}


// function to make a copy of the original BMP image
int copyBMPFile(char *FileName) {
    FILE *inputFile = fopen(FileName, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen("new.bmp", "wb");
    if (outputFile == NULL) {
        perror("Error creating output file");
        fclose(inputFile);
        return 1;
    }

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}



int OpenBmpFile(FILE *fp,char *FileName){
 
    struct BITMAPHeader header;
    struct DIBHeader dibheader;

   
    fread(header.name,2,1,fp);
    fread(&header.size,3*sizeof(int),1,fp);
    // Checking if it's an BMP image
    if(header.name[0] != 'B' || header.name[1] != 'M'){
            fclose(fp);
            return 1;
    }


    
    fread(&dibheader,sizeof(struct DIBHeader),1,fp);
    // Checking if it's an BMP image
    if(dibheader.header_size != 40 || dibheader.compression != 0 || dibheader.bitsperpixel != 24){
        fclose(fp);
        return 1;
    }
    
    printf("%c%c\n",header.name[0],header.name[1]);
    printf("%d\n",header.size);
    printf("%d\n",header.image_offset);
    printf("%d\n %d\n %d\n %d\n %d\n %d\n %d\n",dibheader.header_size,dibheader.width,dibheader.height,dibheader.colorplanes,dibheader.bitsperpixel,dibheader.compression,dibheader.image_size);

    
    fseek(fp,header.image_offset,SEEK_SET);
    // reading image data
    struct Image *pic = NULL;
    pic = readImage(fp,dibheader.width,dibheader.height);

    //make a copy of the image
    copyBMPFile(FileName);

    generalFunctions(header,dibheader,*pic);
    
    //free the image data
    freeImage(pic);
    fclose(fp);
    return 0;
} 
