#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10000000
#define max 10000000
double inicio, fim;
void sequencial(long int *vetor, int n)
{
    for (int i = 0; i < TAMANHO; i++)
    {
        if (vetor[i] == n)
        {
            printf("o valor %d foi encontrado no vetor\n", n);
        }
    }
}

void paralelo(long int *vetor, int n)
{
#pragma omp parallel num_threads(6)
    {
#pragma omp for
        for (int i = 0; i < TAMANHO; i++)
        {
            if (vetor[i] == n)
            {
                printf("[Thread: %d] o valor %d foi encontrado no vetor\n", omp_get_num_threads(),n);
            }
        }
    }
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
        int num = (rand() % (max + 1));
        vetor[i] = num;
    }
    int n = 100;

    // SEQUENCIAL
    inicio = omp_get_wtime();
    sequencial(vetor, n);
    fim = omp_get_wtime();
    double tempoSequencial = fim - inicio;
    printf("Tempo do sequencial: %f\n", tempoSequencial);

    // PARALELO
    inicio = omp_get_wtime();
    paralelo(vetor, n);
    fim = omp_get_wtime();
    double tempoParalelo = fim - inicio;
    printf("Tempo do paralelo: %f\n", tempoParalelo);

    //ANALISES
    double speedup = tempoSequencial/tempoParalelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n",speedup/6.0);

    return 0;
}

