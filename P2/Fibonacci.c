//  Elaboracion: 17/09/2024  
//  Fibonacci
//  Autores:  
//  Martin Eduardo Chacon Orduño - 351840
//  Carlos Esteban Barragán Bernal - 359299
//  Luz Mariam Garcia Castillo - 348409
//  Leonardo Franco Bulkley - 377288

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long int fibonacciRecursivo(int n);
unsigned long long int fibonacciIterativo(int n);

int main(int argc, char const *argv[])
{
    int opt;
    int num;
    clock_t start, end;
    double cpuTimeUsed;
    do {
        printf("\nMenu: \n1) Serie de Fibonacci para numero n.\n2) Numero n de Fibonacci.\n9) Salir.\nOpcion: ");
        scanf("%i", &opt);
        
        switch (opt){
            case 1:
                printf("\nSerie de Fibonacci\n");
                printf("Inserte el numero de la serie de fibonacci que quiere conocer: ");
                scanf("%i", &num);
                printf("\nFibonacci Recursivo:\n");
                start = clock();
                for (int i=0; i<=num; i++){
                    printf("%llu, ", fibonacciRecursivo(i));
                }
                end = clock();
                cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("\nTiempo de ejecucion: %f\n \n", cpuTimeUsed);

                start = clock();
                printf("\nFibonacci Iterativo:\n");
                for (int i=0; i<=num; i++){
                    printf("%llu, ", fibonacciIterativo(i));
                }
                end = clock();
                cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("\nTiempo de ejecucion: %f\n \n", cpuTimeUsed);
                break;
            case 2:
                printf("\nNumero de Fibonacci.\n");
                printf("Inserte el numero de fibonacci que quiere conocer: ");
                scanf("%i", &num);
                printf("\nFibonacci Recursivo:\n");
                start = clock();
                printf("F(%i) = %llu ",num, fibonacciRecursivo(num));
                end = clock();
                cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("\nTiempo de ejecucion: %f\n \n", cpuTimeUsed);

                start = clock();
                printf("\nFibonacci Iterativo:\n");
                printf("F(%i) = %llu ",num, fibonacciIterativo(num));
                end = clock();
                cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("\nTiempo de ejecucion: %f\n \n", cpuTimeUsed);
                break;
            case 9:
                printf("Gracias por usar este programa.");
                break;
        }
    } while (opt != 9);

    return 0;
}

unsigned long long int fibonacciRecursivo(int n){
if (n < 2){
    return n;
}
else {
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}
}

unsigned long long int fibonacciIterativo(int n){
    if (n==0)
        return 0;
    if (n==1)
        return 1;

    unsigned long long int fib1, fib2, fibr;
    fib1 = 0;
    fib2 = 1;
    for (int i = 2; i <= n; i++){
        fibr = fib1 + fib2;
        fib1 = fib2;
        fib2 = fibr;
    }
    return fibr;
}