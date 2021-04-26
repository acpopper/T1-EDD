#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"

typedef struct nodo Nodo;
typedef struct pixel Pixel ;

struct nodo {
  int n_pixeles;
  int U;
  Pixel* head;
  Nodo* parent;
} ;

struct pixel {
  int umbral;
  int pos;
  Pixel* next;
} ;

int** matrix_init(Image* image);
void show_matriz(Image* image);
bool se_repite_numero(int* arreglo, int n, int num);
int* generar_escala(Image* image, int* c);
void imprimir_arreglo(int* arr, int n);
