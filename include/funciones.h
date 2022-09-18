#ifndef _FUNCIONES_
#define _FUNCIONES_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct dataPGM{
    char filePath[50];
    char type[3];
    uint8_t **data;
    int width, height;
    unsigned int maxValue;
} dataPGM;

//PGM File structure: https://users.wpi.edu/~cfurlong/me-593n/pgmimage.html#:~:text=PGM%20is%20a%20standard%20bitmap,8%2Dbit%20data%20per%20pixel.
int obtenerDatosPGM(dataPGM *pgmStruct, const char *nombreArchivo);
void ignorarComentarios(FILE *archivo);
void imprimirDatos(dataPGM *pgmStruct);


#endif