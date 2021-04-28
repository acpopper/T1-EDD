#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../imagelib/image.h"
#include "extras.h"

//como instanciar escala de imagen:
// int n_escala;
// int* escala = generar_escala(image, &n_escala);

// como instanciar vecinos de un pixel
// int* vecinos=NULL;
// pos_vecinos(matrix, w, h, i, j, &vecinos);

Nodo* nodo_init(int U)
{
  Nodo* nodo = malloc(sizeof(Nodo));
  *nodo = (Nodo) {
    .U=U,
    .n_pixeles=0,
    .parent=NULL,
    .head=NULL,
    .next=NULL,
    .pix=NULL
  };
  return nodo;
}

Pixel* pixel_init(int pos)
{
  Pixel* pixel = malloc(sizeof(Pixel));
  *pixel = (Pixel) {
    .pos=pos,
    .next= NULL
  };
  return pixel;
}

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

void show_matrix(int** matrix, int h, int w){
    
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
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

int* generar_escala(Image* image, int* c)
{   
    int n=image->pixel_count;
    int* arr=image->pixels;
    int* escala = calloc(n, sizeof(int));
    int contador=0;
    
    // armar lista sin repetidos
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
    
    //ordenar 
    for(int i = 1; i < contador; i++) {
        int numero = new[i];
        int j = i - 1;
        while (j >= 0 && new[j] > numero) {
            new[j + 1] = new[j];
            j = j - 1;
        }
        new[j + 1] = numero;
    }
    // paso la lista de tonos a calloc
    int* new2 = calloc(contador, sizeof(int));
    for(int i=0; i<contador; i++){
        new2[i]=new[i];
    }
    
    free(escala);
    *c = contador;
    return new2;
}
 
void imprimir_arreglo(int* arr, int n){
    for (int i = 0; i < n; i++)
        printf("%i ", arr[i]);

    printf("\n");
}

void add_pixel_to_nodo(int pos, Nodo* nodo){
    Pixel* pixel = pixel_init(pos);
    if(!nodo->pix){
        nodo->pix=pixel;
    }
    else{
        Pixel* current = nodo->pix;
        while (current->next && current->pos!=pos){
            current=current->next;
        }
        if(current->pos!=pos){
            current->next=pixel;
        }
            
    }
    nodo->n_pixeles+=1;
}

void show_full_list(List* all_nodos){
    List* current_nodo = all_nodos;
    while(current_nodo){
        printf("Umbral del nodo: %i\n", current_nodo->value->U);
        Pixel* current_pixel = current_nodo->value->pix;
        while(current_pixel){
            printf("    P: %i\n", current_pixel->pos);
            current_pixel = current_pixel->next;
        }
        current_nodo=current_nodo->next;
    }
}

void pos_vecinos(int** matrix, int w, int h, int posi, int posj,int **array)
{
    free(*array);
    
    *array = malloc(5 * sizeof(int));

    int offsetx[]={1, 0, -1, 0};
    int offsety[]={0, 1, 0, -1};
    
    for (int t = 0; t < 4; t++){
    //  printf("iter %i\n", t);
        printf("x %i y %i\n", (posi+offsetx[t]), (posj+offsety[t]));
        if((posi+offsetx[t])<0 || (posi+offsetx[t])>(h-1) || (posj+offsety[t])<0 || (posj+offsety[t])>(w-1)){
            (*array)[t] = -1;
            // printf("if vecino %i\n", (*array)[t]);
        } 
        else if(matrix[posi][posj]<=matrix[posi+offsetx[t]][posj+offsety[t]]){
                (*array)[t]=w*(posi+offsetx[t])+(posj+offsety[t]);
                // printf("elif vecino %i\n", matrix[posi+offsetx[t]][posj+offsety[t]]);
        }
        else{
            (*array)[t] = -1;
            // printf("else vecino %i\n", matrix[posi+offsetx[t]][posj+offsety[t]]);
        }
    }
    printf("x %i y %i\n", posi, posj);
    (*array)[4]=w*(posi)+(posj);
    
    // for(int p=0;p<5;p++){
    //     printf("%i ", (*array)[p]);
    // }
    // printf("\n");
}



List* list_init(Nodo* nodo)
{
  List* list = malloc(sizeof(List));

  *list = (List) {
    .value = nodo,
    .next = NULL, 
  };
  return list;
}

void list_append(List* list, Nodo* nodo)
{
  List *last = list;
  while (last->next) {
    last = last->next;
  }

  List *new_list = list_init(nodo);

  last->next = new_list;
}

// editar para que se destruyan los nodos
void list_destroy(List *list)
{
  if (list->next)
  {
    list_destroy(list->next);
  }
  free(list);
}

bool is_algun_vecino_in_nodo(int* pos, Nodo* nodo){
    Pixel* current=nodo->pix;
    for(int i=0; i<5;i++){
        while(current){
            if(current->pos==pos[i]){
                return true;
            }
        }
    }
    return false;
}
// reviso si está el pixel o alguno de sus vecinos en alguno de los nodos con su mismo umbral
Nodo* is_algun_vecino_in_all_no2(int* pos, List* all_nodos, int umbral){
    List* nodo_current = all_nodos;
    while(nodo_current){
        if(nodo_current->value->U==umbral){
            Pixel* current_pix=nodo_current->value->pix;
            for(int i=0; i<5;i++){
                if(pos[i]>=0){
                    while(current_pix){
                        if(current_pix->pos==pos[i]){
                            return nodo_current->value;
                        }
                        current_pix=current_pix->next;
                    }
                }   
            }
        }
        nodo_current=nodo_current->next;
    }
    return NULL;
}

void armar_lista_maestra(int* escala, int n_escala, List* all_nodos, int** matrix, int w, int h){
    for(int e=1; e<n_escala; e++){
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                if(matrix[i][j]==e){
                    int* vecinos=NULL;
                    pos_vecinos(matrix, w, h, i, j, &vecinos);
                    Nodo* chosen = is_algun_vecino_in_all_no2(vecinos, all_nodos, e);
                    if(chosen){
                        for(int v=0; v<5; v++){
                            add_pixel_to_nodo(vecinos[v], chosen);
                        }
                    }
                    else{
                        Nodo* new = nodo_init(e);
                        for(int v=0; v<5; v++){
                            add_pixel_to_nodo(vecinos[v], new);
                        }
                        list_append(all_nodos, new);
                    }
                }
            }
        }
    }
}