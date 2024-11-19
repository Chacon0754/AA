//  Elaboracion: 01/11/2024
//  SelectionSort
//  Autores:
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *originalarr = NULL;
int *arr = NULL;
long long exchanges;
long long comparisons;
int arraySize;
int totalElements;

void shellSort();
void showArray(int size);
void readFile(char filename[20]);

int main(int argc, char const *argv[])
{
    clock_t start, end;
    double cpuTimeUsed;
    int testSizes[] = {50, 100, 1000, 10000, 100000, 1000000};
    int numTests = sizeof(testSizes) / sizeof(testSizes[0]);
    int option;
    char filename[20];

    do {
        printf("\nSeleccione un archivo para las pruebas:\n");
        printf("1. bestCase.txt\n");
        printf("2. averageCase.txt\n");
        printf("3. worstCase.txt\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option){
            case 1:
                snprintf(filename, sizeof(filename), "bestCase.txt");
                break;
            case 2:
                snprintf(filename, sizeof(filename), "averageCase.txt");
                break;
            case 3:
                snprintf(filename, sizeof(filename), "worstCase.txt");
                break;
            case 0:
                printf("Saliendo del programa\n");
                return 0;
            default:
                printf("Opcion invalida. Intente de nuevo\n");
                continue;
        }

        readFile(filename);

        if (originalarr == NULL){
            printf("Error al leer el archivo o al asignar memoria\n");
            continue;
        }

        for (int i = 0; i < numTests; i++){

            arraySize = testSizes[i];

            arr = (int *)malloc(arraySize * sizeof(int));
            if (arr == NULL){
                printf("No se pudo asignar memoria al arreglo\n");
                continue;
            }

            for (int j = 0; j < arraySize; j++)
            {
                arr[j] = originalarr[j];
            }

            printf("\nProbando con arreglo de tamano: %d\n", arraySize);
            if (arraySize <= 100){
                printf("Arreglo original:\n");
                showArray(arraySize);
            }

            start = clock();
            shellSort();
            end = clock();

            cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;

            if (arraySize <= 100){
                printf("\nArreglo ordenado:\n");
                showArray(arraySize);
            }

            printf("\nComparaciones: %lld. Intercambios: %lld. Tiempo usado: %f segundos\n", comparisons, exchanges, cpuTimeUsed);
            free(arr);
            arr = NULL;
        }

        free(originalarr);
        originalarr = NULL;

    } while (option != 0);

    return 0;
}

void shellSort(){
    int gap, i, j, temp;
    comparisons = exchanges = 0;
    for (gap = arraySize / 2; gap > 0; gap /= 2){
        for (i = gap; i < arraySize; i++){
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                comparisons++;
                arr[j] = arr[j - gap];
                exchanges++;
            }
            if (j >= gap){
                comparisons++;
            }
            arr[j] = temp;
            exchanges++;
        }
    }
}

void showArray(int size){
    for (int i = 0; i < size; i++){
        printf("%i, ", arr[i]);
    }
    printf("\n");
}

void readFile(char filename[20]){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    totalElements = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1){
        totalElements++;
    }

    originalarr = (int *)malloc(totalElements * sizeof(int));
    if (originalarr == NULL){
        printf("No se pudo asignar memoria para el arreglo\n");
        fclose(file);
        return;
    }

    rewind(file);
    for (int i = 0; i < totalElements; i++){
        fscanf(file, "%d", &originalarr[i]);
    }

    fclose(file);
}