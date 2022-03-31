#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define ITERATIONS 1000000000

int calculatePI(double *piTotal) {
    int i = 0;
    do{
        *piTotal = *piTotal + (double)(4.0 / ((i*2) + 1));
        i++;
        *piTotal = *piTotal - (double)(4.0 / ((i*2) + 1));
        i++;
    } while( i < ITERATIONS);

    return 0;
}

int main(int argc, const char* argv[]) {
	double pi;
    pi = 0;
    calculatePI(&pi);
    printf("\npi: %2.10f \n", pi)
}