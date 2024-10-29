#include <stdio.h>
#include <time.h>

void insertionSort(int arr[], int n, int *comparisons);
void printArray(int arr[], int n);

// Función principal
int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int comparisons = 0;

    printf("Arreglo original: \n");
    printArray(arr, n);

    clock_t start, end;
    start = clock();
    insertionSort(arr, n, &comparisons);
    end = clock();

    double time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Arreglo ordenado: \n");
    printArray(arr, n);
    printf("Numero de comparaciones: %d\n", comparisons);
    printf("Tiempo de ejecucion: %f segundos\n", time);

    return 0;
}
// Función para realizar Insertion Sort
void insertionSort(int arr[], int n, int *comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Mueve los elementos de arr[0..i-1] que sean mayores que key, una posición adelante de su posición actual
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j--;
        }
        if (j >= 0){
            (*comparisons)++;
        }
        arr[j + 1] = key;
    }
}

// Función para imprimir el arreglo
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}