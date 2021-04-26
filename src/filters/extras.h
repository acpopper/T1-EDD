#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"



int** matrix_init(Image* image);
void show_matriz(Image* image);
bool se_repite_numero(int* arreglo, int n, int num);
int* generar_escala(Image* image);
void imprimir_arreglo(int* arr, int n);
