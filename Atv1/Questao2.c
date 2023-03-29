#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
double inicio, fim;

int main()
{
    static long num_steps = 100000000;
    double step;
    int i;
    double x, pi, sum = 0.0;
    int t = omp_get_num_threads();
    printf("Theads: %d\n", t);
    inicio = omp_get_wtime();
    step = 1.0 / (double)num_steps;
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;            // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x * x); // Sum += Área do retângulo
    }
    pi = step * sum;
    fim = omp_get_wtime();
    printf("\nSEQUENCIAL ----------\n");
    printf("%.5f\n", pi);
    double tempoSeq = fim - inicio;
    printf("%f\n", tempoSeq);
    pi, sum = 0.0;
    inicio = omp_get_wtime();
#pragma omp parallel private(x) num_threads(6)
    {
#pragma omp for reduction(+ \
                          : sum)
        for (i = 0; i < num_steps; i++)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }
    }
    pi = step * sum;
    fim = omp_get_wtime();
    printf("\nPARALELO ----------\n");
    printf("%.5f\n", pi);
    double tempoPal = fim - inicio;
    printf("%f\n", tempoPal);

    printf("\n--ANALISE--\n");
    printf("Speedup: %.4f, Eficiencia: %.4f", tempoSeq/tempoPal, tempoSeq/tempoPal/6);
    return 0;
}