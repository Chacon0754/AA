//  Elaboracion: 11/11/2024
//  QuickSort
//  Autores:
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *originalarr = NULL;
int *arr = NULL;
long long exchanges;
long long comparisons;
int arraySize;
int totalElements;

void quickSort(int low, int high);
int partition(int low, int high);
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
        printf("2. AverageCase.txt\n");
        printf("3. WorstCase.txt\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option){
            case 1:
                snprintf(filename, sizeof(filename), "bestCase.txt");
                break;
            case 2:
                snprintf(filename, sizeof(filename), "AverageCase.txt");
                break;
            case 3:
                snprintf(filename, sizeof(filename), "WorstCase.txt");
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

            printf("Probando con arreglo de tamano: %d\n", arraySize);
            if (arraySize <= 100){
                printf("Arreglo original:\n");
                showArray(arraySize);
            }

            start = clock();
            quickSort(0, arraySize - 1);
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
        system("pause");
        system("cls");

    } while (option != 0);

    return 0;
}

void quickSort(int low, int high){
    if (low < high){
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int partition(int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    int temp;

    for (int j = low; j < high; j++){
        comparisons++;
        if (arr[j] < pivot){
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            exchanges++;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    exchanges++;

    return i + 1;
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
