#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"
#include "extras.h"


int main(int argc, char** argv)
{
    // Revisamos los argumentos
    if(argc < 4) {
        printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
        return 1;
    }

    // Cargamos la imagen original desde el archivo
    Image* image = img_png_read_from_file(argv[1]);
    
    // obtengo matriz con coordenadas cart.
    int** m=matrix_init(image);
    show_matrix(m, image->height, image->width);
    
    // obtengo escala de los tonos que hay en la foto
    int n_escala;
    int* escala = generar_escala(image, &n_escala);

    // nodo inicial, agrego todos los pixeles como LL
    Nodo* root = nodo_init(escala[0]);
    // agrego root a la lista de todos los nodos por haber
    List* all_nodos=list_init(root);
    for(int p=0; p<image->pixel_count;p++){
        add_pixel_to_nodo(p, root);
    }
    
    show_full_list(all_nodos);
    printf("pixeles totales: %i\n", all_nodos->value->n_pixeles);

    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(image->pixel_count, sizeof(int))
    };

    // Filtramos el arbol y lo guardamos en la imagen, segun el filtro que corresponda
    if (! strcmp("delta", argv[3]))
    {
        // Filtro DELTA
        float max_delta = atof(argv[4]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro delta y     */
        /* guardar la imagen filtrada en new_img.       */

    }
    else if (! strcmp("area", argv[3]))
    {
        // Filtro AREA-COLOR
        int min_area = atoi(argv[4]);
        int threshold = atoi(argv[5]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro de area y   */
        /* guardar la imagen filtrada en new_img.       */
        
    }

    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    printf("Listo!\n");

    // Liberamos los recursos
    img_png_destroy(image);
    img_png_destroy(new_img);

    // Terminamos exitosamente
    return 0;
}