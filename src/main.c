# include "../include/funciones.h"

#define imagen "./res/imagen_full.pgm"
#define pedazo "./res/pedazo_buscar.pgm"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("Error missing number of threads: binary [num_threads]\n");
        exit(0);
    }

    int num_threads = atoi(argv[1]);
    if(num_threads < 0){
       num_threads = 1; //Serial run 
    }

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
    buscarPedazo(imagenFull, pedazoBuscar, num_threads);

    free(imagenFull);
    free(pedazoBuscar);
    return 0;
}