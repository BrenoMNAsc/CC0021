#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_THREADS 4
#define MAX 1000000000
double inicial, final;
int main() {
    // sequencial
    inicial = omp_get_wtime();
    double soma = 0;
    int i = 0;
    for(i = 1; i <= MAX; i++){
        if(MAX%i == 0) soma+=i;
    }
    final = omp_get_wtime();
    double t_sequencial = final - inicial;
    printf("\nSoma sequencial: %f\n Tempo Sequencial: %f\n", soma, t_sequencial);

    //Explicitando uma região crítica
    inicial = omp_get_wtime();
    double somaPar = 0;
    double somaPar2 = 0;
    i = 0;
    #pragma omp parallel private(somaPar2) num_threads(NUM_THREADS)
    {
        #pragma omp for
            for(i = 1; i <= MAX; i++){
                if(MAX%i == 0){
                    somaPar2 += i;
                }
            }
        #pragma omp critical
                somaPar+=somaPar2;
    }
    final = omp_get_wtime();
    double t_paraleloCrit = final - inicial;
    printf("\n(Região CRITICA)\nSoma paralela: %f\n Tempo Paralelo: %f\n", somaPar, t_paraleloCrit);


    //Redução com for estático
    inicial = omp_get_wtime();
    double somaParEsta = 0;
    i = 0;
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for schedule(static) reduction (+: somaParEsta)
            for(i = 1; i <= MAX; i++){
            if(MAX%i == 0){
                somaParEsta+=i;
            }
            }
    }
    final = omp_get_wtime();
    double t_paraleloEsta = final - inicial;
    printf("\n(ESTATICA)\nSoma paralela: %f\n Tempo Paralelo: %f\n", somaParEsta, t_paraleloEsta);

    //Redução com for estático
    inicial = omp_get_wtime();
    double somaParDin = 0;
    i = 0;
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for schedule(dynamic) reduction (+: somaParDin)
            for(i = 1; i <= MAX; i++){
            if(MAX%i == 0){
                somaParDin+=i;
            }
            }
    }
    final = omp_get_wtime();
    double t_paraleloDin = final - inicial;
    printf("\n(DINAMICO)\nSoma paralela: %f\n Tempo Paralelo: %f\n", somaParDin, t_paraleloDin);







    //
    printf("(Região CRITICA) Speedup: %f\n ", t_sequencial/t_paraleloCrit);
    printf("(ESTATICA) Speedup: %f\n", t_sequencial/t_paraleloEsta);
    printf("(DINAMICA) Speedup: %f\n", t_sequencial/t_paraleloDin);
    return 0;
}