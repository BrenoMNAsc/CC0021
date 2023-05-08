#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define max 100000

double insertionSort(int *v, int n){
    int i = 0;
    int j = 1;
    int aux = 0;
    double time_i = omp_get_wtime();
    for(j = 1; j< n; j++){
        aux = v[j];
        for(i = j-1; i >= 0 && v[i]>aux; i--){
                v[i + 1] = v[i];
        }
        v[i + 1] = aux;
    }
    double time_f = omp_get_wtime() - time_i;
    return time_f;
}

double insertionSortParallel(int *v, int n){
    int i = 0;
    int j = 1;
    int aux = 0;
    double time_i = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
        for(j = 1; j< n; j++){
        aux = v[j];
        for(i = j-1; i >= 0 && v[i]>aux; i--){
                v[i + 1] = v[i];
        }
        v[i + 1] = aux;
        }
    }
    double time_f = omp_get_wtime() - time_i;
    return time_f;    
}

int main(){
    int v[max];
    int v2[max];
    for(int i = 0; i < max; i++){
        v[i] = rand() % 100000;
        v2[i] = v[i];
    }
    double timeSerial = insertionSort(v, max);
    double timeParalelo = insertionSortParallel(v2, max);
    for(int i = 0; i < max; i++){
        printf("%d,", v2[i]);
    }
    printf("\n%f\n", timeSerial);
    printf("%f\n", timeParalelo);
}
