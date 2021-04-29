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
        nodo->n_pixeles+=1;
    }
    else{
        
        Pixel* current = nodo->pix;
        while (current->next && current->pos!=pos){
            current=current->next;
        }
        if(current->pos!=pos){
            current->next=pixel;
            nodo->n_pixeles+=1;
        }
        else{
            free(pixel);
        }
    }
    
}

void show_full_list(List* all_nodos){
    List* current_nodo = all_nodos;
    while(current_nodo){
        printf("Umbral del nodo: %i, cantidad de pixeles: %i\n", current_nodo->value->U, current_nodo->value->n_pixeles);
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
        // printf("x %i y %i\n", (posi+offsetx[t]), (posj+offsety[t]));
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
    // printf("x %i y %i\n", posi, posj);
    (*array)[4]=w*(posi)+(posj);
    
    // for(int p=0;p<5;p++){
    //     printf("%i ", (*array)[p]);
    // }
    // printf("\n");
}

void show_pixeles_en_nodo(Nodo* nodo){
    Pixel* current_pixel = nodo->pix;    
    while(current_pixel){
        printf("Pixel: %i\n", current_pixel->pos);
        current_pixel = current_pixel->next;
    }
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

List2* list2_init(int value)
{
  List2* list2 = malloc(sizeof(List2));

  *list2 = (List2) {
    .value = value,
    .next = NULL, 
  };
  return list2;
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

void list2_append(List2* list, int value)
{
  List2 *last = list;
  while (last->next) {
    last = last->next;
  }
  List2 *new_list = list2_init(value);
  last->next = new_list;
}

bool pixel_is_in_list2(List2* list2, int num){
    List2* current_pixel = list2;    
    while(current_pixel){
        if(current_pixel->value==num){
            return true;
        }
        current_pixel = current_pixel->next;
    }
    return false;
}

void list2_destroy(List2 *list)
{
  if (list->next)
  {
    list2_destroy(list->next);
  }
  free(list);
}

// reviso si está el pixel o alguno de sus vecinos en alguno de los nodos con su mismo umbral
Nodo* is_algun_vecino_in_all_no3(List2* elem, List* all_nodos, int umbral){
    List* nodo_current = NULL;
    if(all_nodos->next){
        nodo_current = all_nodos->next;
    }
    while(nodo_current){
        if(nodo_current->value->U==umbral){
            List2* current_pos = elem;
            while(current_pos){
                Pixel* current_pix=nodo_current->value->pix;
                while(current_pix){
                    if(current_pix->pos==current_pos->value){
                        return nodo_current->value;
                    }
                    current_pix=current_pix->next;
                }
                current_pos=current_pos->next;                
            }                 
        }
        nodo_current=nodo_current->next;
    }
    return NULL;
}

void pos_vecinos_version_pro(int** matrix, int w, int h, int posi, int posj, List2* elem, int e){   

    int offsetx[]={1, 0, -1, 0};
    int offsety[]={0, 1, 0, -1};
    
    for (int t = 0; t < 4; t++){
        if((posi+offsetx[t])<0 || (posi+offsetx[t])>(h-1) || (posj+offsety[t])<0 || (posj+offsety[t])>(w-1)){
            continue;
        } 
        else if(matrix[posi+offsetx[t]][posj+offsety[t]]>=e){            
            if(!pixel_is_in_list2(elem, w*(posi+offsetx[t])+(posj+offsety[t]))){
                list2_append(elem, w*(posi+offsetx[t])+(posj+offsety[t]));
                pos_vecinos_version_pro(matrix, w, h, (posi+offsetx[t]), (posj+offsety[t]), elem, e);
            }                
            }
    }
}


void armar_lista_maestra_version_pro(int* escala, int n_escala, List* all_nodos, int** matrix, int w, int h){
    for(int e=1; e<n_escala; e++){
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                if(matrix[i][j]==escala[e]){
                    List2* aux = list2_init(w*i+j);
                    pos_vecinos_version_pro(matrix, w, h, i, j, aux, escala[e]);
                    Nodo* chosen = is_algun_vecino_in_all_no3(aux, all_nodos, escala[e]);                    
                    if(chosen){
                        List2* current = aux;
                        while(current){
                            add_pixel_to_nodo(current->value, chosen);
                            current=current->next;
                        }                        
                    }
                    else{
                        Nodo* new = nodo_init(escala[e]);
                        List2* current = aux;
                        while(current){
                            add_pixel_to_nodo(current->value, new);
                            current=current->next;
                        }
                        list_append(all_nodos, new);
                    }
                    list2_destroy(aux);
                }
            }
        }
    }
}

void desligar_pixel(Nodo* nodo, int pixel){
    Pixel* current_pixel = nodo->pix;
    while(current_pixel){
        if(current_pixel->pos==pixel){
            printf("Desligando %i de nodo %i\n", pixel, nodo->U);
            Pixel* byebye = nodo->pix;
            nodo->pix=nodo->pix->next;
            free(byebye);
            nodo->n_pixeles -=1;
        }
        if(current_pixel->next && current_pixel->next->pos==pixel){
            printf("Desligando %i de nodo %i\n", pixel, nodo->U);
            Pixel* byebye = current_pixel->next;
            current_pixel->next=current_pixel->next->next;
            free(byebye);
            nodo->n_pixeles -=1;
        }
        current_pixel=current_pixel->next;
    }
    
}

void de_lista_a_arbol(List* all_nodos){
    printf("Entró a func\n");
    List* nodo_parent = all_nodos;
    printf("Nodo padre de esta it. %i\n", nodo_parent->value->U);  
    List* nodo_hijo = nodo_parent->next;
    printf("Nodo hijo de esta it. %i\n", nodo_hijo->value->U);
    Pixel* pixel_parent = nodo_parent->value->pix;
    while(pixel_parent){
        printf("Buscando pixel padre: %i\n", pixel_parent->pos);
        while(nodo_hijo){
            if(nodo_hijo->value->U > nodo_parent->value->U){
                Pixel* pixel_hijo = nodo_hijo->value->pix;
                while(pixel_hijo){
                    if(pixel_parent->pos==pixel_hijo->pos){
                        printf("Padre %i Hijo %i calzan en pix %i\n", nodo_parent->value->U, nodo_hijo->value->U, pixel_hijo->pos);                        
                        ligar_nodos(nodo_parent->value, nodo_hijo->value);
                        // printf("se va a desligar %i de %i\n", pixel_parent->pos, nodo_parent->value->U);
                        desligar_pixel(nodo_parent->value, pixel_parent->pos);
                        // printf("Va a entrar nodo hijo %i\n", nodo_hijo->value->U);
                        de_lista_a_arbol(nodo_hijo);
                    }
                    pixel_hijo=pixel_hijo->next;
                }
            }
        nodo_hijo=nodo_hijo->next;
        }
        pixel_parent=pixel_parent->next;

    }
}


void ligar_nodos(Nodo* parent, Nodo* hijo){
    if(!parent->head){
        parent->head=hijo;
    }
    else{
        Nodo* last = parent->head;
        while(last->next){
            last=last->next;
        }
        last->next=hijo;
    }
    hijo->parent=parent;
    printf("Nodo padre %i se ha ligado con %i\n", parent->U, hijo->U);
}

