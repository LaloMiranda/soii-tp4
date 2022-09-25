# include "../include/funciones.h"

#define imagen "../res/imagen_full.pgm"
#define pedazo "../res/pedazo_buscar.pgm"

int main()
{
    dataPGM *imagenFull = malloc(sizeof(dataPGM));
    dataPGM *pedazoBuscar = malloc(sizeof(dataPGM));
    strcat(imagenFull->filePath, imagen);
    strcat(pedazoBuscar->filePath, imagen);

    int res = 0;

    res = obtenerDatosPGM(imagenFull, imagen);
    if(res == 1){
        exit(EXIT_FAILURE);
    }

    res = obtenerDatosPGM(pedazoBuscar, pedazo);
    if(res == 1){
        exit(EXIT_FAILURE);
    }

    imprimirDatos(imagenFull);
    imprimirDatos(pedazoBuscar);
    printf("\n");

    //imprimirData(imagenFull);
    //imprimirData(pedazoBuscar);

    printf("Buscando imagen\n");
    buscarPedazo(imagenFull, pedazoBuscar);

    free(imagenFull);
    free(pedazoBuscar);
    return 0;
}
