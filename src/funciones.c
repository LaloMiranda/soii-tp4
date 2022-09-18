# include "../include/funciones.h"

int obtenerDatosPGM(dataPGM *pgmStruct, const char *nombreArchivo){
    int res = 0;
    
    FILE *pgmFile = fopen(nombreArchivo, "rb");
    if(pgmFile == NULL){
        printf("El archivo %s no existe\n", nombreArchivo);
        return 1;
    }

    res = fscanf(pgmFile, "%s", pgmStruct->type);
    if(res < 0){
        printf("Error al obtener el tipo de archivo\n");
        return 1;
    }

    res = strcmp(pgmStruct->type, "P5");
    if(res != 0){
        printf("El archivo %s no es de tipo PGM\n", nombreArchivo);
        return 1;
    }

    ignorarComentarios(pgmFile);

    res = fscanf(pgmFile, "%d %d", &(pgmStruct->width), &(pgmStruct->height));
    if(res < 0){
        printf("Error al obtener dimensiones del archivo: %s\n", nombreArchivo);
        exit(1);
    }
    
    res = fscanf(pgmFile, "%u", &(pgmStruct->maxValue));
    if(res < 0){
        printf("Error al obtener valores maximos del archivo: %s\n", nombreArchivo);
        exit(1);
    }

    fclose(pgmFile);
    return 0;
}

void ignorarComentarios(FILE *archivo){
    int ch;
    char line[100];

    // Ignore cualquier linea blanca
    while ((ch = fgetc(archivo)) != EOF && isspace(ch))
        ;

    // Recursively ignore comments
    // Lo que comience con #
    if (ch == '#')
    {
        if (fgets(line, sizeof(line), archivo) == NULL)
        {
            printf("Error al leer la linea\n");
            exit(EXIT_FAILURE);
        }
        ignorarComentarios(archivo);
    }
    else
        fseek(archivo, -1, SEEK_CUR);
}

void imprimirDatos(dataPGM *pgmStruct){
    printf("Archivo: %s\n", pgmStruct->filePath);
    printf("Tipo de archivo: %s\n", pgmStruct->type);
    printf("Ancho de la imagen: %d px\n", pgmStruct->width);
    printf("Alto de la imagen: %d px\n", pgmStruct->height);
    printf("Valor maximo: %d\n", pgmStruct->maxValue);
}