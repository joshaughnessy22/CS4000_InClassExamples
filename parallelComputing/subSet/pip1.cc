
/* File: pi.c
 * Purpose: Estimate pi
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int main(int argc, char *argv[])
{
    int n = 1000;
    double factor = 1.0;
    double sum = 0.0;
    int thread_count = 4;
    if (argc == 2)
        n = atoi(argv[1]);
// unprotected data dependency
#pragma omp parallel for num_threads(thread_count) reduction(+ : sum)
    for (int iter = 0; iter < n; iter++)
    {
        sum += factor / (2 * iter + 1); //sum is protected by the reduction clause
        factor = -factor; //factor is not protected, causing incorrect values
    }
    double pi_approx = 4.0 * sum;
    printf("After %d interations with %d threads, PI is approximately %3.10lf\n", n,
           thread_count, pi_approx);
}
