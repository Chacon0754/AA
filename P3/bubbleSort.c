#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arr[] = {1, 2, 3, 4, 5, 7, 6};
int counter;
int exchanges;
int comparisons;

void bubbleSort();
void showArray();
int arraySize();

int main(int argc, char const *argv[])
{
    clock_t start, end;
    double cpuTimeUsed;
    printf("Original array:\n");
    showArray();
    start = clock();
    bubbleSort();
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nOrdered array:\n");
    showArray();
    printf("\nComparisons: %i. Exchanges: %i. Time used: %f", comparisons, exchanges, cpuTimeUsed);
    return 0;
}

void bubbleSort()
{
    exchanges, comparisons = 0;

    int n = arraySize();
    counter = n;
    for (int i = 0; i < n && counter != 0; i++)
    {
        counter = 0;
        comparisons++;
        for (int j = 0; j <= n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                counter++;
                exchanges++;
            }
        }
    }
}

void showArray()
{
    int n = arraySize();
    for (int i = 0; i < n; i++)
    {
        printf("%i, ", arr[i]);
    }
}

int arraySize()
{
    int len = sizeof(arr) / sizeof(arr[0]);
    return len;
}
