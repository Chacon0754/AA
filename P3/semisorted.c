#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillSemiSortedArray(int arr[], int n) {
    int blockSize = n / 10;  // Tamaño del bloque como 10% del arreglo
    int lowerBound, upperBound;

    for (int i = 0; i < n; i += blockSize) {
        lowerBound = i;
        upperBound = i + blockSize - 1;

        // Llenar el bloque con valores aleatorios dentro del rango
        for (int j = i; j < i + blockSize && j < n; j++) {
            arr[j] = (rand() % blockSize) + lowerBound;
        }
    }
}

void muestra(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n,*arr;
    printf("Introduce el tamaño del arreglo: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("El tamaño del arreglo debe ser un número positivo.\n");
        return 1;
    }

    arr=(int *)malloc(sizeof(int)*n);
    srand(time(0));
    fillSemiSortedArray(arr, n);

    printf("Arreglo semiordenado:\n");
    muestra(arr, n);

    return 0;
}
