
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
    if (argc == 2)
        n = atoi(argv[1]);
    for (int iter = 0; iter < n; iter++)
    {
        sum += factor / (2 * iter + 1);
        factor = -factor;
    }
    double pi_approx = 4.0 * sum;
    printf("After %d interations, PI is approximately %3.10lf\n", n, pi_approx);
}
