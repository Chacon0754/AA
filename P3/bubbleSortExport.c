#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 50  // Límite para los primeros 50 elementos

int *originalArr = NULL;
int *arr = NULL;
int counter;
long long exchanges;
long long comparisons;
int arraySize;
int totalElements;

int current_i = 0; // Para mantener el estado del ordenamiento
int current_j = 0; // Para mantener el estado del ordenamiento

__declspec(dllexport) void bubbleSortStep();
__declspec(dllexport) void showArray(int size);
__declspec(dllexport) void readFile(char filename[20]);
__declspec(dllexport) int getTotalElements();
__declspec(dllexport) int* getOriginalArray();

void bubbleSortStep() {
    if (totalElements <= 1) return; // No hay nada que ordenar si el tamaño es <= 1

    if (current_j >= totalElements - 1 - current_i) {
        current_j = 0;
        current_i++;
    }

    if (current_i < totalElements - 1) {
        comparisons++;
        if (originalArr[current_j] > originalArr[current_j + 1]) {
            // Intercambiar elementos
            int temp = originalArr[current_j];
            originalArr[current_j] = originalArr[current_j + 1];
            originalArr[current_j + 1] = temp;
            exchanges++;
        }
        current_j++;
    }
}

void showArray(int size) {
    for (int i = 0; i < size; i++) {
        printf("%i, ", originalArr[i]);
    }
    printf("\n");
}

void readFile(char filename[20]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    totalElements = 0;
    int temp;

    originalArr = (int *)malloc(MAX_ELEMENTS * sizeof(int));
    if (originalArr == NULL) {
        printf("No se pudo asignar memoria para el arreglo.\n");
        fclose(file);
        return;
    }

    // Leer solo los primeros MAX_ELEMENTS elementos
    while (fscanf(file, "%d", &temp) == 1 && totalElements < MAX_ELEMENTS) {
        originalArr[totalElements++] = temp;
    }

    fclose(file);

    // Reiniciar los índices para el ordenamiento paso a paso
    current_i = 0;
    current_j = 0;
}

int getTotalElements() {
    return totalElements;
}

int* getOriginalArray() {
    return originalArr;
}
