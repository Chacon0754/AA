//  Autores:  
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de funciones
void merge(int arr[], int izq, int medio, int der);
void mergeSort(int arr[], int izq, int der);
void readFiles(int *arreglo, int size, const char *nombreArchivo);
void randomNumbers(int *arr, int size);

// Variable global para contar el número de comparaciones
int contadorComparaciones = 0;

int main(int argc, const char *argv[]) {
    int opcion;
    do {
        printf("Menu:\n");
        printf("1. Ordenar arreglo desde archivo\n");
        printf("2. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: {
                int t;
                char nombreArchivo[100];

                // Pedir el tamaño del arreglo al usuario
                printf("Ingrese el tamaño del arreglo: ");
                scanf("%d", &t);

                // Pedir el nombre del archivo al usuario
                printf("Ingrese el nombre del archivo de datos: ");
                scanf("%s", nombreArchivo);

                // Crear el arreglo dinámicamente
                int *arreglo = (int *)malloc(t * sizeof(int));
                if (arreglo == NULL) {
                    printf("No se pudo asignar memoria.\n");
                    return 1;
                }

                // Llenar el arreglo con números del archivo
                readFiles(arreglo, t, nombreArchivo);
                
                //Aleatorizar la entrada
                randomNumbers(arreglo, t);
                // Medir el tiempo de ejecución de Merge Sort
                clock_t inicio = clock();
                mergeSort(arreglo, 0, t - 1);
                clock_t fin = clock();

                double tiempo_transcurrido = (double)(fin - inicio) / CLOCKS_PER_SEC;
                printf("Tiempo transcurrido: %f segundos\n", tiempo_transcurrido);

                // Mostrar el arreglo ordenado si es pequeño
                if (t < 1000) {
                    printf("Arreglo ordenado:\n");
                    for (int i = 0; i < t; i++)
                        printf("%d ", arreglo[i]);
                    printf("\n");
                }

                // Mostrar el número total de comparaciones realizadas
                printf("Número total de comparaciones: %d\n", contadorComparaciones);

                // Liberar la memoria asignada
                free(arreglo);

                // Reiniciar el contador de comparaciones para la siguiente ejecución
                contadorComparaciones = 0;

                break;
            }
            case 2:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while(opcion != 2);

    return 0;
}

// Función para leer los números del archivo
void readFiles(int *arreglo, int size, const char *nombreArchivo) {
    FILE *file;

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

void randomNumbers(int *arr, int size){
    srand(time(0));
    int ni =  (rand() % (size)/2);
    int a;
    int b;
    int temp;
    printf("\nSize: %i. ni: %i.\n", size, ni);
    // printf("Arreglo original");
    // for (int i = 0; i < size;i++){
    //     printf("indice: %i Valor: %i\n", i, arr[i]);
    // }

    for (int i = 0; i < ni; i++){
        
        a = (rand() % (size));
        b = (rand() % (size));
        temp = arr[a];
        // printf("\na: %i, b: %i, temp: %i", a, b, temp);
        arr[a] = arr[b];
        arr[b] = temp;
    }
    // printf("\nArreglo modificado\n");
    // for (int i = 0; i < size;i++){
    //     printf("indice: %i Valor: %i\n", i, arr[i]);
    // }
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

    if (L == NULL || R == NULL) {
        printf("No se pudo asignar memoria para los arreglos temporales.\n");
        exit(1);
    }

    // Copiar datos a los arreglos temporales L[] y R[]
    for (i = 0; i < n1; i++) {
        L[i] = arr[izq + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[medio + 1 + j];
    }

    // Fusionar los arreglos temporales de nuevo en arr[izq..der]
    i = 0;
    j = 0;
    k = izq;
    while (i < n1 && j < n2) {
        contadorComparaciones++; // Comparación en el while
        if (L[i] <= R[j]) {
            contadorComparaciones++; // Comparación en el if
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
        contadorComparaciones++; // Comparación en el while
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        contadorComparaciones++; // Comparación en el while
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
    contadorComparaciones++; // Comparación en el if
    if (izq < der) {
        //TODO int medio cambiar por numero aleatorio entre izquiero y derecho
        int medio = izq + (der - izq) / 2;

        mergeSort(arr, izq, medio);
        mergeSort(arr, medio + 1, der);

        // Fusionar los subarreglos ordenados
        merge(arr, izq, medio, der);
    }
}
