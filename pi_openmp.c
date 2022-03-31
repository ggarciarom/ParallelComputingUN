#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8
#define ITERATIONS 1000000000

int calculatePI(double *piTotal, int ID) {
    int start, end;

    start = (ITERATIONS/omp_get_num_threads()) * ID;
    end = (ITERATIONS/omp_get_num_threads()) * (ID + 1);

    int i = start;
    do{
        *piTotal = *piTotal + (double)(4.0 / ((i*2) + 1));
        i++;
        *piTotal = *piTotal - (double)(4.0 / ((i*2) + 1));
        i++;
    } while( i < end);
    return 0;
}

int main(int argc, const char* argv[]) {

    int i, threads = NUM_THREADS;
	double start, delta, pi[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++)
    {
        pi[i] = 0;
    }

    start = omp_get_wtime();
    #pragma omp parallel num_threads(threads){
        int ID = omp_get_thread_num();
        calculatePI(pi, ID);
    }
	delta = omp_get_wtime() - start;
    
    for (i = 1; i < NUM_THREADS; i++)
    {
        pi[0] = pi[i] + pi[0];
    }

    printf("\npi: %2.10f \n", pi[0])
	printf("Computed in %.4g seconds with %d threads.\n", delta, NUM_THREADS);
}