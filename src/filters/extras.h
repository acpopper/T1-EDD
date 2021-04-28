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


int** matrix_init(Image* image);
void show_matrix(int** matrix, int h, int w);
bool se_repite_numero(int* arreglo, int n, int num);
int* generar_escala(Image* image, int* c);
void imprimir_arreglo(int* arr, int n);
void pos_vecinos(int** matrix, int w, int h, int posi, int posj,int **array, int length);
List* list_init(Nodo* value);
void list_append(List* list, int umbral);
void list_destroy(List *list);
void add_pixel_to_nodo(int pos, Nodo* nodo);
bool is_algun_vecino_in_nodo(int* pos, Nodo* nodo);
bool is_algun_vecino_in_all_no2(int* pos, List* all_nodos, int umbral);