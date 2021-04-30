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
  struct list* prev;
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
void list2_destroy(List2 *list);
void add_pixel_to_nodo(int pos, Nodo* nodo);
void show_full_list(List* all_nodos);
Nodo* is_algun_vecino_in_all_no3(List2* elem, List* all_nodos, int umbral);
void pos_vecinos_version_pro(int** matrix, int w, int h, int posi, int posj, List2* elem, int e);
void armar_lista_maestra_version_pro(int* escala, int n_escala, List* all_nodos, int** matrix, int w, int h);
bool pixel_is_in_list2(List2* list2, int num);
void desligar_pixel(Nodo* nodo, int pixel);
void de_lista_a_arbol(List* all_nodos);
void ligar_nodos(Nodo* parent, Nodo* hijo);
void iterative_lista_a_arbol(List* nodo_lista);
void print_max_tree(Nodo* nodo, int n);
void tree_to_array(Nodo* arbol, int* arr);
void area_filter(Nodo* max_tree, int A, int G);
int get_pixeles_vecindario(Nodo* maxtree, int p);