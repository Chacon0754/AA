#include <stdio.h>
#include <stdlib.h>

int arr[] = {6, 7, 8, 10, 5, 4, 1, 9, 20, 89};
int counter;

void bubbleSort();
void showArray();
int arraySize();


int main(int argc, char const *argv[])
{
    printf("Original array:\n");
    showArray();
    bubbleSort();
    printf("\n\nOrdered array:\n");
    showArray();
    return 0;
}


void bubbleSort(){
    int n = arraySize();
    counter = n;
    for (int i = 0; i < n && counter != 0; i++){
        for (int j = 0; j <= n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                counter++;
            }
        }
    }
}

void showArray(){
    int n = arraySize();
    for (int i = 0; i < n; i++){
        printf("%i, ", arr[i]);
    }
}

int arraySize(){
    int len = sizeof(arr) / sizeof(arr[0]);
    return len;
}
