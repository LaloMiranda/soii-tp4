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

    fgetc(pgmFile);

    //Aloco la matriz de datos
    pgmStruct->data = alloc_matrix(pgmStruct->height, pgmStruct->width);

    for (int i = 0; i < pgmStruct->height; i++){
        for (int j = 0; j < pgmStruct->width; j++){
         pgmStruct->data[i][j] = fgetc(pgmFile);   
        }
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

void imprimirData(dataPGM *pgmStruct){
    for (int i = 0; i < pgmStruct->height; i++)
    {
        for (int j = 0; j < pgmStruct->width; j++)
        {
            printf("Valor %i: %i\n", (i*pgmStruct->width+1) + j, pgmStruct->data[i][j]);
        }
    }
}

int **alloc_matrix(int heigth, int width) /* Allocate the array y seteo todo cero*/
{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i;
    int **array;
    array = calloc((size_t)heigth, sizeof(int *));
    array[0] = calloc((size_t)(heigth * width), sizeof(int));
    for (i = 0; i < heigth; i++)
        array[i] = array[0] + i * width;
    return array;
}

void buscarPedazo(dataPGM *imgFull, dataPGM *pedazo){
    int boundHeight = imgFull->height - pedazo->height + 1;
    int boundWidth  = imgFull->width - pedazo->width + 1; 
    // int matches = 0;
    #pragma omp parallel num_threads(atoi(getenv("threads")))
    {
    //Recorro la matriz full size
    #pragma omp for
    for (int i = 1; i < boundHeight; i++){
        for (int j = 1; j < boundWidth; j++){
            if(imgFull->data[i][j] == pedazo->data[0][0]){
                //printf("Punta en (%i, %i)\n", i, j);
                if(checkRest(imgFull, pedazo, i, j)){
                    printf("Encontre la matriz en: %i:%i\n", j + pedazo->width/2, i + pedazo->height/2);
                    //return;
                }
                // else{
                //     printf("No match\n");
                // }
            }
        }
    }
    }
    
}

bool checkRest(dataPGM *imgFull, dataPGM *pedazo, int x, int y){
    for (int i = 0; i < pedazo->height; i++)
    {
        for (int j = 0; j < pedazo->width; j++)
        {
            //printf("%i ? %i\n", imgFull->data[x + i][y + j], pedazo->data[i][j]);
            if(imgFull->data[x + i][y + j] != pedazo->data[i][j]){
                return false;
            }
        }
    }
    return true;
    
}