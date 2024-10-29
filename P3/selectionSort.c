#include <stdio.h>
#include <time.h>

void selectionSort(int arr[], int n, int *comparisons);
void printArray(int arr[], int n);



int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int comparisons = 0;

    clock_t start, end;
    start = clock();

    selectionSort(arr, n, &comparisons);

    end = clock();

    double time = ((double)(end - start)) / CLOCKS_PER_SEC;


    printf("Arreglo ordenado: \n");
    printArray(arr, n);

    printf("Numero de comparaciones: %d\n", comparisons);
    printf("Tiempo de ejecucion: %f segundos\n", time);

    return 0;
}

void selectionSort(int arr[], int n, int *comparisons) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        // Encuentra el elemento mínimo en el arreglo no ordenado
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++; 
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        // Intercambia el elemento mínimo con el primer elemento no ordenado
        if (min != i) {
            int temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}