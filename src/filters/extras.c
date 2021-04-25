#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"
#include "extras.h"


int** matrix_init(Image* image){
    int cont = 0;
    int** matrix = calloc(image->height, sizeof(int*));
    for(int row = 0; row < image->height; row++){
        matrix[row] = calloc(image->width, sizeof(int));
        for(int col = 0; col < image->width; col++){
            matrix[row][col]= image->pixels[cont];
            cont+=1;
        }
    }
    return matrix;
} 

void show_matriz(Image* image){
    
    for(int i=0; i<image->pixel_count;i++){
        printf("%i, ", image->pixels[i]);
        if(!((i+1)%image->width&&i!=(image->pixel_count-1))){
            printf("\n");
        }
    }
    
}






