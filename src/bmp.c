#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


//function that give color to  the pixel for drawing
void paint(rgb_t *pixel,rgb_t color){
    rgb_t temp;
    temp.red = color.red;
    temp.green = color.green;
    temp.blue = color.blue;
    *pixel = temp;
}

// this function use Bresenham's Line Algorithm to draw lines
void draw(app_t *newEdit,int x1,int y1,int x2,int y2){

    int32_t dx = abs((int32_t)x2 - (int32_t)x1);
    int32_t sx = x1 < x2 ? 1 : -1;
    int32_t dy = -abs((int32_t)y2 - (int32_t)y1);
    int32_t sy = y1 < y2 ? 1 : -1;
    int32_t err = dx + dy;

    while (1) {
        paint(&newEdit->opened_image->rgb[x1][y1],newEdit->brush_settings.brush_color);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int32_t e2 = 2 * err;

        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
    
}

// function that draw lines on the image
//INFO:it's draws only simple straight and diagonals lines
void draw_line(app_t *newEdit){
   
    int x1,y1,x2,y2;
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

    for(int i = 0; i<=newEdit->brush_settings.brush_size;i++){
        if(x1 == x2){
            draw(newEdit,x1+i,y1,x2+i,y2);
        }else if(y1 == y2){
            draw(newEdit,x1,y1+i,x2,y2+i);
        }else{
            draw(newEdit,x1+i,y1,x2+i,y2);
        }   
    }

    write_image(newEdit);
    
}

//function that draws the square on the image
void draw_square(app_t *newEdit){
    

    int x1,y1,x2,y2;
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

    for(int i = 0; i<=newEdit->brush_settings.brush_size;i++){
        draw(newEdit,x1+i,y1,x1+i,y2);
        draw(newEdit,x2+i,y1,x2+i,y2);
        draw(newEdit,x1,y1+i,x2,y1+i);
        draw(newEdit,x1,y2+i,x2,y2+i);
        draw(newEdit,x2+i,y1+i,x2+i,y2+i);
        draw(newEdit,x1+i,y2+i,x2+i,y2+i);
        
    }

    write_image(newEdit);

}


//function that draws the triangle on the image
void draw_triangle(app_t *newEdit){

    int x1,y1,x2,y2,x3,y3;
    scanf("%d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3);

    //I used here x2 y2 as the top angle of triangle  
    for(int i = 0; i<=newEdit->brush_settings.brush_size;i++){

        if(x1 == x3){
            draw(newEdit,x1-i,y1,x3-i,y3);
            draw(newEdit,x1-i,y1,x2-i,y2);
            draw(newEdit,x3-i,y3,x2-i,y2);

        }else if(y1 == y3){
            if(y2 > y1){
                if(x1 < x3){
                    draw(newEdit,x1-newEdit->brush_settings.brush_size,y1-i,x3,y3-i);
                }else{
                    draw(newEdit,x1,y1-i,x3-newEdit->brush_settings.brush_size,y3-i);
                }
            }else{
                if(x1 < x3){
                    draw(newEdit,x1-newEdit->brush_settings.brush_size,y1+i,x3,y3+i);
                }else{
                    draw(newEdit,x1,y1+i,x3-newEdit->brush_settings.brush_size,y3+i);
                }
            }
            
            draw(newEdit,x1-i,y1,x2-i,y2);
            draw(newEdit,x3-i,y3,x2-i,y2); 
        }
           
    }

    write_image(newEdit);
}

// function where you change the color and the size of the brush
void mod_cl_or_size(app_t *newEdit){
    int32_t r, g, b;
    int32_t size;

    scanf("%d%d%d%d", &r, &g, &b, &size);

    while (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0) {
        fprintf(stderr, "<Error>: Incorrect rgb value (%d, %d, %d)\n", r, g, b);
        scanf("%d%d%d", &r, &g, &b);
    }

    newEdit->brush_settings.brush_color.red = (uint8_t)r;
    newEdit->brush_settings.brush_color.green = (uint8_t)g;
    newEdit->brush_settings.brush_color.blue = (uint8_t)b;

    while (size <= 0 || size > 255) {
        fprintf(stderr, "<Error>: size too small/big [%d]\n", size);
        scanf("%d", &size);
    }

    newEdit->brush_settings.brush_size = (uint16_t)size;
}


// function from where you can change the image
void general_functions(app_t *newEdit){
    printf("<App>: [Image info] : %dx%d\n", newEdit->opened_image->infoDIB.width, newEdit->opened_image->infoDIB.height);
    
    int num = 1;
    //if you dont change the color it's will be set from the start as black
    newEdit->brush_settings.brush_color.red = 0;
    newEdit->brush_settings.brush_color.green = 0;
    newEdit->brush_settings.brush_color.blue = 0;

    while(num != 0){
        printf("<App>: [0 - Exit] [1 - Line] [2 - Square] [3 - Triangle] [4 - Brush]\n");
        printf("<App>: ");
        scanf("%d",&num);

        if(num == 0)break;

        switch (num){
        case 1:
            printf("<App>: [Draw a line] : (x1, y1) -> (x2, y2)\n");
            draw_line(newEdit);
            break;
        case 2:
            printf("<App>: [Draw a square] : corner_1 -> opposite_corner_1\n");
            printf("<App>: [Draw a square] : (x1, y1) -> (x2, y2)\n");
            draw_square(newEdit);
            break;
        case 3:
            printf("<App>: [Draw a triangle] : (x1, y1) -> (x2, y2) -> (x3, y3)\n");
            draw_triangle(newEdit);
            break;
        case 4:
            printf("<App>: [Brush settings] : color -> size\n");
            printf("<App>: [Brush settings] : (r, g, b) -> (size)\n");
            mod_cl_or_size(newEdit);
            break;
        default:
            break;
        }
    }

}
