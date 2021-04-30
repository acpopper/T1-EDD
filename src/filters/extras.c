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
    .prev = NULL 
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
  new_list->prev=last;
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
        if(nodo->pix && nodo->pix->pos==pixel){
            nodo->pix=nodo->pix->next;
            free(nodo->pix);
            nodo->n_pixeles -=1;
        }
        else if(current_pixel->next && current_pixel->next->pos==pixel){
            Pixel* aux = current_pixel->next;
            current_pixel->next=current_pixel->next->next;
            free(aux);
            nodo->n_pixeles -=1;
        }
        
        current_pixel=current_pixel->next;
    }
    
} 

void de_lista_a_arbol(List* all_nodos){
    List* last = all_nodos;
    while(last->next){
        last=last->next;
    }
    iterative_lista_a_arbol(last);
    all_nodos->value->n_pixeles-=1;
    all_nodos->value->pix=all_nodos->value->pix->next;
}

void iterative_lista_a_arbol(List* nodo_lista){
    List* current_nodo_lista = nodo_lista;
    while(current_nodo_lista){
        List* nodo_prev = nodo_lista->prev;
        while(nodo_prev && nodo_prev->value->U>=current_nodo_lista->value->U){
            // printf("Current U %i, prev U %i\n", current_nodo_lista->value->U, nodo_prev->value->U);
            nodo_prev=nodo_prev->prev;
        }
        while(nodo_prev){
            
            Pixel* pix_chico = current_nodo_lista->value->pix;
            while(pix_chico){
                Pixel* compare = nodo_prev->value->pix;
                while(compare){
                    if(pix_chico->pos==compare->pos){
                        ligar_nodos(nodo_prev->value, current_nodo_lista->value);
                        desligar_pixel(nodo_prev->value, pix_chico->pos);
                    }
                    compare=compare->next;
                }
                pix_chico=pix_chico->next;
            }
            
            nodo_prev=nodo_prev->prev;
        }
        current_nodo_lista=current_nodo_lista->prev;
    }
}



void ligar_nodos(Nodo* parent, Nodo* hijo){
    if(!hijo->parent){
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
    }
    else if(hijo->parent->U<parent->U){
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
    }
}

void print_max_tree(Nodo* nodo, int n){
    printf("%*sNodo: %i, n_pix: %i\n", n, "", nodo->U, nodo->n_pixeles);
    Nodo* current = nodo->head;
  
    while (current){
        print_max_tree(current, n+4);
        current = current->next;
    }
}

void tree_to_array(Nodo* arbol, int* arr){
    Pixel* current_pixel = arbol->pix;
    while(current_pixel){
        arr[current_pixel->pos]=arbol->U;
        current_pixel=current_pixel->next;
    }

    Nodo* current = arbol->head;
    while (current){
        tree_to_array(current, arr);
        current = current->next;
    }
}

void area_filter(Nodo* max_tree, int A, int G){
    if(max_tree->U<=G || get_pixeles_vecindario(max_tree, 0)<=A){
       if(!max_tree->parent){
           max_tree->U=0;
       }
       else{
           max_tree->U=max_tree->parent->U;
       }
   }
    Nodo* current = max_tree->head;
    while (current){
        area_filter(current, A, G);
        current = current->next;
    }
}

int get_pixeles_vecindario(Nodo* maxtree, int p){
    p+=maxtree->n_pixeles;
    Nodo* current = maxtree->head;
    while (current){
        get_pixeles_vecindario(current, p);
        current = current->next;
    }
    return p;
}
