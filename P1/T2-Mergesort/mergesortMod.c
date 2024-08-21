#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int izq, int medio, int der);
void mergeSort(int arr[], int izq, int der);
void readFiles(int *arreglo, int size);

int main(int argc, const char * argv[]) {
    
    int t;

    // Pedir el tamaño del arreglo al usuario
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &t);

    // Crear el arreglo dinámicamente
    int *arreglo = (int *)malloc(t * sizeof(int));
    if (arreglo == NULL) {
        printf("No se pudo asignar memoria.\n");
        return 1;
    }

    // Llenar el arreglo con números del archivo
    readFiles(arreglo, t);

    // Medir el tiempo de ejecución de Merge Sort
    clock_t inicio = clock();
    mergeSort(arreglo, 0, t - 1);
    clock_t fin = clock();

    double tiempo_transcurrido = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo transcurrido: %f segundos\n", tiempo_transcurrido);

    // Mostrar el arreglo ordenado
    if(t < 1000)
    {
        printf("Arreglo ordenado:\n");
        for (int i = 0; i < t; i++)
            printf("%d ", arreglo[i]);
        printf("\n");
    }

    // Liberar la memoria asignada
    free(arreglo);

    return 0;
}

// Función para leer los números del archivo
void readFiles(int *arreglo, int size) {
    FILE *file;
    const char *nombreArchivo = "peor.txt";

    // Abrir el archivo en modo lectura
    file = fopen(nombreArchivo, "r");
    if (file == NULL) {
        printf("No se puede abrir el archivo %s.\n", nombreArchivo);
        exit(1);
    }

    // Leer los números del archivo y almacenarlos en el arreglo
    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &arreglo[i]) != 1) {
            printf("No se pudieron leer suficientes números del archivo.\n");
            fclose(file);
            exit(1);
        }
    }

    // Cerrar el archivo
    fclose(file);
}

// Función para fusionar dos subarreglos
void merge(int arr[], int izq, int medio, int der) {
    int i, j, k;
    int n1 = medio - izq + 1;
    int n2 = der - medio;
    int *L, *R;

    // Crear arreglos temporales
    L = (int *)malloc(n1 * sizeof(int));
    R = (int *)malloc(n2 * sizeof(int));

    // Copiar datos a los arreglos temporales L[] y R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[izq + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    // Fusionar los arreglos temporales de nuevo en arr[izq..der]
    i = 0;
    j = 0;
    k = izq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar la memoria asignada a los arreglos temporales
    free(L);
    free(R);
}

// Función de ordenación Merge Sort
void mergeSort(int arr[], int izq, int der) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;

        mergeSort(arr, izq, medio);
        mergeSort(arr, medio + 1, der);

        // Fusionar los subarreglos ordenados
        merge(arr, izq, medio, der);
    }
}


