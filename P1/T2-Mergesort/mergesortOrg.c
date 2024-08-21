
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void merge(int arr[], int izq, int medio, int der);
void mergeSort(int arr[], int izq, int der);
void llenarConAleatorios(int *arreglo, int tama);

int main(int argc, const char * argv[]) {
    
        int t,i;

        // Pedir el tamaño del arreglo al usuario
        printf("Ingrese el tamaño del arreglo: ");
        scanf("%d", &t);

        // Crear el arreglo dinámicamente
        int *arreglo = (int *)malloc(t * sizeof(int));
        if (arreglo == NULL) {
            printf("No se pudo asignar memoria.\n");
            return 1;
        }

        // Llenar el arreglo con números aleatorios
        llenarConAleatorios(arreglo, t);

        // Medir el tiempo de ejecución de Merge Sort
        clock_t inicio = clock();
        mergeSort(arreglo, 0, t - 1);
        clock_t fin = clock();

        double tiempo_transcurrido = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido: %f segundos\n", tiempo_transcurrido);

        // Mostrar el arreglo ordenado
        if(t<1000)
        {
            printf("Arreglo ordenado:\n");
    
            for ( i = 0; i < t; i++)
                printf("%d ", arreglo[i]);
        }
        printf("\n");

        // Liberar la memoria asignada
        free(arreglo);

        return 0;
    }





// Función para fusionar dos subarreglos
void merge(int arr[], int izq, int medio, int der) {
    int i, j, k;
    int n1 = medio - izq + 1;
    int n2 = der - medio;
    int *L,*R;
    // Crear arreglos temporales
   // int L[n1], R[n2];
    L = (int *)malloc(sizeof(int)*n1);
    R = (int *)malloc(sizeof(int)*n2);
    // Copiar datos a los arreglos temporales L[] y R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[izq + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    // Fusionar los arreglos temporales de nuevo en arr[izq..der]
    i = 0; // Índice inicial del primer subarreglo
    j = 0; // Índice inicial del segundo subarreglo
    k = izq; // Índice inicial del subarreglo fusionado
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

// Función para llenar un arreglo con números aleatorios entre 0 y 1000
void llenarConAleatorios(int *arreglo, int tama) {
    int i;
    srand(time(0));
    for ( i = 0; i < tama; i++) {
        arreglo[i] = rand() % 1001;
    }
}
