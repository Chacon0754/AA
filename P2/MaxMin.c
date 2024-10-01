//  Elaboracion: 24/09/2024  
//  Máximo y Mínimo
//  Autores:  
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288

#include <stdio.h>


typedef struct {
    int minimum;
    int maximum;
} MinMax;

MinMax findMinMax(int arr[], int start, int end);

int main(int argc, char const *argv[])
{
    // int arr[] = {150, 40, 60, 8, 9, 20};
    // int n = sizeof(arr) / sizeof(arr[0]);

    int n;
    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) !=1 || n<= 0){
        printf("Invalid number of elements. \n");
        return 1;
    }

    int *arr  = (int *)malloc(n * sizeof(int));

    if (arr == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    generateUnorderedArray(arr, n);  // Generamos el arreglo

    MinMax result = findMinMax(arr, 0, n - 1);
    printf("Minimum: %d\n", result.minimum);
    printf("Maximum: %d\n", result.maximum);

    free(arr);
    return 0;
    system("pause");
}

MinMax findMinMax(int arr[], int start, int end){
    MinMax result, left, right;

    if (start == end){
        result.minimum = arr[start];
        result.maximum = arr[start];
        return result;
    }

    else if (end == start + 1){
        if (arr[start]< arr[end]){
            result.minimum = arr[start];
            result.maximum = arr[end];
        } else {
            result.minimum = arr[end];
            result.maximum = arr[start];
        }
        return result;
    }

    int mid = (start + end) / 2;
    left = findMinMax(arr, start, mid);
    right = findMinMax(arr, mid + 1, end);

    result.minimum = (left.minimum < right.minimum) ? left.minimum : right.minimum;
    result.maximum = (left.maximum > right.maximum) ? left.maximum : right.maximum;

    return result;
}
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