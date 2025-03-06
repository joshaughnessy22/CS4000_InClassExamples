
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
    long long int fibo[10000];
    long long int n = 100;
    fibo[0] = fibo[1] = 1;
    for (int i = 2; i < n; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    for (int i = 0; i < 20; i++)
        printf("%lld ", fibo[i]);
    printf("\n");
    printf("fib(%lld) = %lld\n", n, fibo[n - 1]);
}
