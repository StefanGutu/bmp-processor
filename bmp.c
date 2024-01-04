#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

unsigned char grayscale(rgb_t rgb){
    return ((0.3*rgb.red) + (0.6*rgb.green) + (0.1*rgb.blue));
}


// converts an RGB image in an Gray image
void rgb_to_gray(image_t *pic){
    
    for(uint32_t i = 0; i < pic->infoDIB.height;i++){
        for(uint32_t j = 0;j < pic->infoDIB.width;j++){
            pic->rgb[i][j].red = grayscale(pic->rgb[i][j]);
            pic->rgb[i][j].green = grayscale(pic->rgb[i][j]);
            pic->rgb[i][j].blue = grayscale(pic->rgb[i][j]);
        }
    }
}

void create_bw_image(image_t *pic){
    
    FILE *fp = fopen("new.bmp","rb+");


    rgb_to_gray(pic);
    write_image(pic);
    
    fclose(fp);
}

//Make an image with TEXT
void image_to_text(image_t *pic){

    FILE *fp = fopen("new.bmp","rb+");
    

    char txtPixel[] = {'#','$','%','&','Q','Y','U','O'};
    unsigned char gs;

    for(int32_t i = 0;i < pic->infoDIB.height;i++){
        for(int32_t j = 0; j < pic->infoDIB.width;j++){
            gs = grayscale(pic->rgb[i][j]);
            printf("%c",txtPixel[gs/32]);
        }
        printf("\n");
    }

    
    fclose(fp);
}


//function that make the pixel black for drawing
void paint_black(rgb_t *pixel){
    rgb_t temp;
    temp.red = 0;
    temp.green = 0;
    temp.blue = 0;
    *pixel = temp;
}

void drawing_lines_on_matrix(image_t *pic){
    int x1,y1,x2,y2;
    printf("Enter the coordinates\n");
    printf("x1 y1 x2 y2:\n");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    
    if(y1 == y2){
        for(int32_t i = 0; i < pic->infoDIB.height;i++){
            for(int32_t j = 0;j < pic->infoDIB.width;j++){
                if(i == y1 && (((j>=x1) && (j<=x2))|| ((j<=x1) && (j>=x2)))){
                    paint_black(&pic->rgb[i][j]);
                }
            }
        }
    }else if(x1 == x2){
        for(int32_t i = 0; i < pic->infoDIB.height;i++){
            for(int32_t j = 0;j < pic->infoDIB.width;j++){
                if(j == x1 && (((i>=y1) && (i<=y2))|| ((i<=y1) && (i>=y2)))){
                    paint_black(&pic->rgb[i][j]);
                }
            }
        }
    }else{
        for(int32_t i = 0; i < pic->infoDIB.height;i++){
            for(int32_t j = 0;j < pic->infoDIB.width;j++){
                if((((j>=x1) && (j<=x2))|| ((j<=x1) && (j>=x2))) && (((i>=y1) && (i<=y2))|| ((i<=y1) && (i>=y2))) && (x1 == y1) && (i == j)){
                        paint_black(&pic->rgb[i][j]);
                }else if((x1 == y2) && (i + j == pic->infoDIB.width - 1) &&  (((i>=y1) && (i<=y2))|| ((i<=y1) && (i>=y2)))){
                        paint_black(&pic->rgb[i][j]);
                }
            }
        }
       
    }

}


// function that draw lines on the image
void draw_line(image_t *pic){
   
    
    drawing_lines_on_matrix(pic);

    write_image(pic);
    ;
}

void drawing_square_on_matrix(image_t *pic){
    int x1,y1,x2,y2;
    printf("Enter the coordinates\n");
    printf("x1 y1 x2 y2:\n");
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

    for(int32_t i = 0;i<pic->infoDIB.height;i++){
        for(int32_t j = 0;j<pic->infoDIB.width;j++){
            if(((i == y1) && (j >= x1 && j <=x2)) || ((i == y2) && (j >= x1 && j <=x2))  || ((j == x1) && (i > y1 && i < y2)) ||  ((j == x2) && (i > y1 && i < y2)) ){
                paint_black(&pic->rgb[i][j]);
            }
        }
    }

}

//function that draws the square on the image
void draw_square(image_t *pic){
    

    drawing_square_on_matrix(pic);

    write_image(pic);

}

void drawing_traingle_on_matrix(image_t *pic){
    int x1,y1,x2,y2,x3;
    printf("Enter the coordinates\n");
    printf("x1 y1 x2 y2 x3:\n");
    scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&x3);
    
    int secondDiagonal = x1 + y1;

    for(int32_t i = 0; i < pic->infoDIB.height;i++){
        for(int32_t j = 0;j < pic->infoDIB.width;j++){
            if (i >= y1 && i <= y2 && ((j - x1) * (y2 - y1) == (i - y1) * (x3 - x1))) {
            paint_black(&pic->rgb[i][j]);
        }
            if (j >= x2 && j <= x1 && i >= y1 && i <= y2 && secondDiagonal == i + j) {
                paint_black(&pic->rgb[i][j]);
            }
            if (i == y2 && j >= x2 && j <= x3) {
                paint_black(&pic->rgb[i][j]);
            }
                
        }
    }

}

//function that draws the triangle on the image
void draw_triangle(image_t *pic){
    

    drawing_traingle_on_matrix(pic);
    write_image(pic);



}


// function from where you can change the image
void general_functions(image_t *pic){
    
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
            create_bw_image(pic);
            break;
        case 2:
            image_to_text(pic);
            break;
        case 3:
            draw_line(pic);
            break;
        case 4:
            draw_square(pic);
            break;
        case 5:
            draw_triangle(pic);
            break;
        default:
            break;
        }
    }

}
