#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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


bool se_repite_numero(int* arreglo, int n, int num){
    
    for(int i = 0; i < n; i++){
        if(arreglo[i] == num){
            return true;
        }
    }
    return false;
}

int* generar_escala(Image* image)
{   
    int n=image->pixel_count;
    int* arr=image->pixels;
    int* escala = calloc(n, sizeof(int));
    int contador=0;
    
    for(int i=1; i<n;i++){
        if(!se_repite_numero(escala, contador, arr[i])){
            escala[contador]=arr[i];
            contador+=1;
        }
    }
    int new[contador];
    for(int i=0; i<contador; i++){
        new[i]=escala[i];
    }
    
    
    for(int i = 1; i < contador; i++) {
        int numero = new[i];
        int j = i - 1;
        while (j >= 0 && new[j] > numero) {
            new[j + 1] = new[j];
            j = j - 1;
        }
        new[j + 1] = numero;
    }
    int* new2 = calloc(contador, sizeof(int));
    for(int i=0; i<contador; i++){
        new2[i]=new[i];
    }
    
    free(escala);
    return new2;
}
 
void imprimir_arreglo(int* arr, int n){
    for (int i = 0; i < n; i++)
        printf("%i ", arr[i]);

    printf("\n");
}


 


