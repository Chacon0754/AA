//  Elaboracion: 30/09/2024  
//  Búsqueda
//  Autores:  
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función de búsqueda recursiva
int search(int arr[], int start, int end, int target) {
    if (start == end) {  // Caso base: subarreglo de un solo elemento
        if (arr[start] == target) {
            return start;  // Retornamos el índice si lo encontramos
        } else {
            return -1;  // No se encontrado
        }
    }

    int mid = (start + end) / 2;  // Dividir arreglo

    int leftResult = search(arr, start, mid, target);  // Búsqueda en la primera mitad (izquierda)

    if (leftResult != -1) {
        return leftResult;  // Si lo encontramos en la mitad izquierda, devolver la posición
    }

    return search(arr, mid + 1, end, target);  // Si no, buscamos en la segunda mitad
}

// Función generar arreglo desordenado
void generateUnorderedArray(int arr[], int n) {
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  // Generar números aleatorios entre 0 y 99
    }

    printf("Generated unordered array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    
    printf("Enter the size of the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    generateUnorderedArray(arr, n);  // Generamos el arreglo

    int target;
    printf("Enter the value to search for: ");
    scanf("%d", &target);

    int result = search(arr, 0, n - 1, target);  // Llamamos a la función de búsqueda

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    free(arr);  // Liberamos la memoria
    return 0;
}