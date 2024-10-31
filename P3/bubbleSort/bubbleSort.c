//  Elaboracion: 29/10/2024
//  BubbleSort
//  Autores:
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *originalArr = NULL;
int *arr = NULL;
int counter;
long long exchanges;
long long comparisons;
int arraySize;
int totalElements;

void bubbleSort();
void showArray(int size);
void readFile(char filename[20]);

int main(int argc, char const *argv[])
{
    clock_t start, end;
    double cpuTimeUsed;

    int testSizes[] = {10, 100, 1000, 10000, 100000, 1000001};
    int numTests = sizeof(testSizes) / sizeof(testSizes[0]);

    int option;
    char filename[20];
    do
    {
        printf("\nSeleccione un archivo para las pruebas:\n");
        printf("1. bestCase.txt\n");
        printf("2. averageCase.txt\n");
        printf("3. worstCase.txt\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option)
        {
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
            printf("Saliendo del programa.\n");
            return 0;
        default:
            printf("Opcion invalida. Intente de nuevo.\n");
            continue;
        }
        readFile(filename);

        if (originalArr == NULL)
        {
            printf("No se pudo leer el archivo o hubo un error en la asignacion de memoria.\n");
            continue;
        }

        for (int i = 0; i < numTests; i++)
        {
            arraySize = testSizes[i];

            arr = (int *)malloc(arraySize * sizeof(int));

            if (arr == NULL)
            {
                printf("No se pudo leer el archivo o hubo un error en la asignacion de memoria.\n");
                continue;
            }

            for (int j = 0; j < arraySize; j++)
            {
                arr[j] = originalArr[j];
            }

            printf("\n\nProbando con tamano de arreglo: %d\n", arraySize);
            if (arraySize <= 100)
            {
                printf("Arreglo original:\n");
                showArray(arraySize);
            }

            start = clock();
            bubbleSort();
            end = clock();

            cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;

            if (arraySize <= 100)
            {
                printf("\n\nArreglo ordenado:\n");
                showArray(arraySize);
            }
            printf("\nComparaciones: %lld. Intercambios: %lld. Tiempo usado: %f segundos\n", comparisons, exchanges, cpuTimeUsed);
            free(arr);
            arr = NULL;
        }

        free(originalArr);
        originalArr = NULL;

    } while (option != 0);

    return 0;
}

void bubbleSort()
{
    exchanges = comparisons = 0;

    counter = arraySize;

    for (int i = 0; i < arraySize && counter != 0; i++)
    {
        counter = 0;

        for (int j = 0; j < arraySize - 1 - i; j++)
        {
            comparisons++;
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                counter++;
                exchanges++;
            }
        }
        if (counter == 0)
        {
            break;
        }
    }
}

void showArray(int size)
{

    for (int i = 0; i < size; i++)
    {
        printf("%i, ", arr[i]);
    }
}

void readFile(char filename[20])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    totalElements = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1)
    {
        totalElements++;
    }

    originalArr = (int *)malloc(totalElements * sizeof(int));
    if (originalArr == NULL)
    {
        printf("No se pudo asignar memoria para el arreglo.\n");
        fclose(file);
        return;
    }

    rewind(file);
    for (int i = 0; i < totalElements; i++)
    {
        fscanf(file, "%d", &originalArr[i]);
    }

    fclose(file);
}
