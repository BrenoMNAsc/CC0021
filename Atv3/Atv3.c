#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

double *gerarVetor(int n);

int main() {

    int i;
    int TAMANHO = 100000000;
    time_t t;
    srand(time(NULL));
    double *vetor = NULL;
    double somaS = 0;
    double somaP = 0;
    double tempoInicialSequencial,tempoFinalSequencial;
    double tempoInicialParalelo, tempoFinalParalelo;
    vetor = gerarVetor(TAMANHO);
    
    
    // em sequência
    tempoInicialSequencial = omp_get_wtime(); 
    for (i=0;i<TAMANHO;i++) {
        somaS = somaS + vetor[i];
        
    }
    tempoFinalSequencial = omp_get_wtime();
    

    // em paralelo

    tempoInicialParalelo = omp_get_wtime(); // tempo inicial
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:somaP)
            for (i=0;i<TAMANHO;i++) {
                somaP = somaP + vetor[i];
            }
    }

    tempoFinalParalelo = omp_get_wtime();
    double mediaP = somaP/(double)TAMANHO;
    


    double mediaS = somaS/(double)TAMANHO;
    printf("Sequencial :\n");
    printf("Soma: %lf\n",somaS);
    printf("Media: %lf\n",mediaS);
    double tempoSequencial = tempoFinalSequencial-tempoInicialSequencial;
    printf("Tempo sequencial: %lf\n",tempoSequencial);
    printf("\n");


    printf("Paralelo:\n");
    printf("Soma: %lf\n",somaP);
    printf("Media: %lf\n",mediaP);
    double tempoParalelo = tempoFinalParalelo-tempoInicialParalelo;
    printf("Tempo paralelo: %.4f\n",tempoParalelo);
    double speedup = tempoSequencial/tempoParalelo;
    printf("\n");
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Eficiência: %f\n",eficiencia);
    return 0;
}

double *gerarVetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (double)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}