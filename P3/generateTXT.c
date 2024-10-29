#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000

void generateBestCase();
void generateAverageCase();
void generateWorstCase();

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    generateBestCase();
    generateAverageCase();
    generateWorstCase();
    return 0;
}

void generateBestCase(){
    char fileName[50]  = "bestCase.txt";
    FILE *file = fopen(fileName, "w");

    if (file == NULL){
        printf("No se pudo crear el archivo %s\n", fileName);
        return;
    }

    for (int i = 0; i < MAX; i++){
        fprintf(file, "%d\n", i);
    }
    fprintf(file, "%d", MAX);

    fclose(file);
    printf("Archivo %s creado exitosamente.\n", fileName);
}

void generateAverageCase(){
    char fileName[50]  = "AverageCase.txt";
    FILE *file = fopen(fileName, "w");

    if (file == NULL){
        printf("No se pudo crear el archivo %s\n", fileName);
        return;
    }

    int *numbers = (int *)malloc((MAX + 1) * sizeof(int));
    if (numbers == NULL) {
        printf("No se pudo asignar memoria para el arreglo.\n");
        fclose(file);
        return;
    }

    for (int i = 0; i <= MAX; i++){
        numbers[i] = i;
    }

    for (int i = MAX; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    for (int i = 0; i < MAX; i++){
        fprintf(file, "%d\n", numbers[i]);
    }
    fprintf(file, "%d", numbers[MAX]);

    free(numbers);
    fclose(file);
    printf("Archivo %s creado exitosamente.\n", fileName);
}
void generateWorstCase(){
    char fileName[50]  = "WorstCase.txt";
    FILE *file = fopen(fileName, "w");

    if (file == NULL){
        printf("No se pudo crear el archivo %s\n", fileName);
        return;
    }

    for (int i = MAX; i > 0; i--){
        fprintf(file, "%d\n", i);
    }
    fprintf(file, "%d", 0);

    fclose(file);
    printf("Archivo %s creado exitosamente.\n", fileName);
}