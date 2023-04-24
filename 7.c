#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 10000

int main() {
    float dados[N];
    int i;
    float soma = 0.0, media, soma_quadrados_diff = 0.0, desvio_padrao;

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        dados[i] = (float)rand() / RAND_MAX;
    }

    #pragma omp parallel for reduction(+:soma)
    for (i = 0; i < N; i++) {
        soma += dados[i];
    }
    media = soma / N;

    #pragma omp parallel for reduction(+:soma_quadrados_diff)
    for (i = 0; i < N; i++) {
        float diff = dados[i] - media;
        soma_quadrados_diff += diff * diff;
    }
    desvio_padrao = sqrt(soma_quadrados_diff / N);

    printf("Desvio padrão: %f\n", desvio_padrao);

    return 0;
}