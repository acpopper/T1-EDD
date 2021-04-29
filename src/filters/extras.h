#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"

typedef struct nodo Nodo;
typedef struct pixel Pixel;

struct nodo {
  int n_pixeles;
  int U;
  Pixel* pix;
  Nodo* parent;
  Nodo* head;
  Nodo* next;
} ;

struct pixel {
  int pos;
  Pixel* next;
} ;

typedef struct list {
  Nodo* value;
  struct list* next;
} List;


typedef struct list2 {
  int value;
  struct list2* next;
} List2;

Nodo* nodo_init(int U);
Pixel* pixel_init(int pos);
int** matrix_init(Image* image);
void show_matrix(int** matrix, int h, int w);
bool se_repite_numero(int* arreglo, int n, int num);
int* generar_escala(Image* image, int* c);
void imprimir_arreglo(int* arr, int n);
void pos_vecinos(int** matrix, int w, int h, int posi, int posj,int **array);
List* list_init(Nodo* value);
void list_append(List* list, Nodo* nodo);
void list_destroy(List *list);
void add_pixel_to_nodo(int pos, Nodo* nodo);
bool is_algun_vecino_in_nodo(int* pos, Nodo* nodo);
Nodo* is_algun_vecino_in_all_no2(int* pos, List* all_nodos, int umbral);
void show_full_list(List* all_nodos);
void armar_lista_maestra(int* escala, int n_escala, List* all_nodos, int** matrix, int w, int h);