#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función auxiliar para obtener el valor del dígito en la posición 'exp' (unidad, decena, centena, etc.)
int obtenerMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Función Counting Sort usada por Radix Sort para ordenar según el dígito significativo representado por dig  
void countingSort(int arr[], int n, int exp) {
    int output[n];  // Array de salida que contendrá los números ordenados temporalmente
    int count[10] = {0};  // Inicializamos el contador para cada dígito (0 a 9)
    
    // Contar la aparición de los dígitos
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    // Modificar count[] para que contenga las posiciones finales de los dígitos
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Construir el array de salida
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copiar el array de salida a arr[], de modo que arr[] esté ordenado según el dígito actual
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Función principal para implementar Radix Sort
void radixSort(int arr[], int n) {
    // Encuentra el número máximo para saber cuántos dígitos tiene
    int max = obtenerMax(arr, n);
    
    // Hacer Counting Sort para cada dígito, usando exp como 10^i, donde i es el dígito actual
    for (int digito = 1; max / digito > 0; digito *= 10)
        countingSort(arr, n, digito);
}

// Función para imprimir un array
void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Programa principal
int main() {
      int n;
    
    // Pedir al usuario el tamaño del arreglo
    printf("Introduce el tamaño del arreglo: ");
    scanf("%d", &n);
    
    int arr[n];
    
    // Pedir al usuario que introduzca los elementos del arreglo
    printf("Introduce los elementos del arreglo:\n");
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    printf("Array original:\n");
    imprimirArray(arr, n);
    
    // Medir el tiempo de ejecución
    clock_t inicio, fin;
    double tiempo_usado;

    inicio = clock();  // Registrar el tiempo al inicio de Radix Sort
    radixSort(arr, n);
    fin = clock();  // Registrar el tiempo al final de Radix Sort
    
    // Calcular el tiempo usado en segundos
    tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    
    printf("Array ordenado:\n");
    imprimirArray(arr, n);
    
    // Imprimir el tiempo de ejecución
    printf("Tiempo de ejecución: %f segundos\n", tiempo_usado);
    
    return 0;
}
