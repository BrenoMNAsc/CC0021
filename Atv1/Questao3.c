#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define TAMANHO 500000000
#define MAX 100000
double inicio, fim;

void sequencial(long int *vetor)
{
    long int soma = 0;
    for (int i = 0; i < TAMANHO; i++)
    {
        soma += vetor[i];
    }
    double media = (double)soma / TAMANHO;
    printf("Media sequencial: %.4f\n", media);
}

void paralelo(long int *vetor)
{
    long int soma = 0;
    int i = 0;
    #pragma omp parallel num_threads(6)
    {
        #pragma omp for reduction(+: soma)
        for (i = 0; i < TAMANHO; i++)
        {
            soma += vetor[i];
        }
    }
    double media = (double) soma/ TAMANHO;
    printf("Media paralela: %.4f\n", media);
}

int main()
{
    time_t t;
    srand((unsigned)time(&t));
    // INICIANDO VETOR
    long int *vetor;
    vetor = malloc(TAMANHO * sizeof(long int));
    int i;
    for (i = 0; i < TAMANHO; i++)
    {
        long int num = (rand() % (MAX + 1));
        vetor[i] = num;
    }
    // SEQUENCIAL
    inicio = omp_get_wtime();
    sequencial(vetor);
    fim = omp_get_wtime();
    double tempoSeq = fim - inicio;
    printf("Tempo sequencial: %f\n\n", tempoSeq);
    inicio = omp_get_wtime();
    paralelo(vetor);
    fim = omp_get_wtime();
    double tempoPal = fim - inicio;
    printf("Tempo paralelo: %f\n", tempoPal);

    printf("\n------ANALISE-------\n");
    printf("\tSpeedup: %.4f\n", tempoSeq/tempoPal);
    printf("\tEficiencia: %.4f\n", (tempoSeq/tempoPal)/6);
}