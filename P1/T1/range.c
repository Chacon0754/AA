//  Autores:  
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    int maxDiff;
    double executionTime;
} RangeResult;


int *randomArray(int size);
RangeResult range1(int *nums, int size);
RangeResult range2(int *nums, int size);
RangeResult range3(int *nums, int size);

int main(int argc, char const *argv[])
{
    int size = 0;
    printf("Enter the size of the array: " );
    scanf("%d", &size);
    if (size <= 0){
        printf("Invalid size. size must be a positive integer.\n");
        return 1;
    }

    int *nums = randomArray(size);

    RangeResult result1 = range1(nums, size);
    printf("Range 1: Max Diff = %d, Execution Time = %f seconds\n", result1.maxDiff, result1.executionTime);
    RangeResult result2 = range2(nums, size);
    printf("Range 2: Max Diff = %d, Execution Time = %f seconds\n", result2.maxDiff, result2.executionTime);
    RangeResult result3 = range3(nums, size);
    printf("Range 3: Max Diff = %d, Execution Time = %f seconds\n", result3.maxDiff, result3.executionTime);

    free(nums);

    return 0;
}

int *randomArray(int size){
    int i;

    srand(time(NULL));
    int *nums = (int *)malloc(size * sizeof(int));
    if (nums == NULL){
        printf("Error allocating memory\n");
        ;
    }

    for (i = 0; i < size; i++){
        nums[i] = rand() % 100;
    }

    printf("Size of nums: %d\n", size);
    // printf("Nums filled with random values:\n");
    // for (i = 0; i < size; i++){
    //     printf("%d, ", nums[i]);
    // }
    printf("\n");

    return nums;
}

RangeResult range1(int *nums, int size){\
    clock_t start, end;
    double cpuTimeUsed;
    start = clock();

    int i, j, diff;
    int maxDiff = 0;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            diff = abs(nums[i] - nums[j]);
            if (diff > maxDiff){
                maxDiff = diff;
            }
        }
    }
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    RangeResult result = {maxDiff, cpuTimeUsed};
    return result;
}

RangeResult range2(int *nums, int size){
    clock_t start, end;
    double cpuTimeUsed;
    start = clock();

    int i, j, diff;
    int maxDiff = 0;
    for (i = 0; i < size; i++){
        for (j = i + 1; j < size;j++){
            diff = abs(nums[i] - nums[j]);
            if(diff> maxDiff){
                maxDiff = diff;
            }
        }
    }
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    RangeResult result = {maxDiff, cpuTimeUsed};
    return result;
}

RangeResult range3(int *nums, int size){
    clock_t start, end;
    double cpuTimeUsed;
    start = clock();

    int max, min, i;
    max = min = nums[size - 1];
    for (i = 0; i < size; i++){
        if(nums[i] < min){
            min = nums[i];
        }
        if(nums[i] > max){
            max = nums[i];
        }
    }

    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    RangeResult result = {max - min, cpuTimeUsed};
    return result;
}