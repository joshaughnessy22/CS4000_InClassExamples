
/* File: pi.c
* Purpose: Estimate pi
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int main(int argc, char* argv[]) {
long long int n = 1000;
long double sum = 0.0;
long double factor = 1.0;
int thread_count = 10;
if (argc == 2) n = atoll(argv[1]);
#pragma omp parallel for num_threads (thread_count) \
reduction (+:sum) private (factor)
for (long long int k = 0; k < n; k++) {
if (k%2==0)
factor = 1.0;
else
factor = - 1.0;
sum += factor / (2*k+1);
}
double pi_approx = 4.0 * sum;
printf("After %lld interations with %d threads, PI is approximately %3.20lf\n",
n, thread_count, pi_approx);
# define M_PIl 3.141592653589793238462643383279502884L /* pi */
printf("Error: %3.20Lf\n", pi_approx - M_PIl);
}
