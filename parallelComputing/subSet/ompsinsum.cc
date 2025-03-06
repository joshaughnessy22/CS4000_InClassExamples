
/* File: omp_sin_sum.c
 * Purpose: Compute a sum in which each term is the value of a function
 * applied to a nonnegative integer i and evaluation of the
 * function requires work proportional to i.
 *
 * Compile: gcc -g -Wall -fopenmp -I. -o omp_sin_sum omp_sin_sum.c
 * Usage: ./omp_sin_sum <number of threads> <number of terms>
 *
 * Input: none
 * Output: sum of n terms and elapsed time to compute the sum
 *
 * Notes:
 * 1. The computed sum is
 *
 * sin(0) + sin(1) + . . . + sin(n(n+3)/2)
 *
 * 2. The function f(i) is
 *
 * sin(i(i+1)/2) + sin(i(i+1)/2 + 1) + . . . + sin(i(i+1)/2 + i)
 *
 * 3. The parallel for directive uses a runtime schedule clause. So
 * the environment variable OMP_SCHEDULE should be either
 * "static,n/thread_count" for a block schedule or "static,1"
 * for a cyclic schedule
 * 4. Uses the OpenMP library function omp_get_wtime to take timings.
 * 5. DEBUG flag will print which iterations were assigned to each
 * thread.
 *
 * IPP: Section 5.7 (pp. 236 and ff.)
 */
/*
Do live testing from the command line using things like:
export OMP_SCHEDULE=static,200
export OMP_NUM_THREADS=4
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define DEBUG 1
#ifdef DEBUG
int *iterations;
double *starttime;
double *stoptime;
#endif
void Usage(char *prog_name);
double Sum(long n, int thread_count);
double Check_sum(long n, int thread_count);
double f(long i);
void Print_iters(double start, long n);
int thread_count = 0;
int main(int argc, char *argv[])
{
    double global_result; /* Store result in global_result */
    long n;               /* Number of terms */
    double start, finish;
    double error, check;
    printf("Try things like: export OMP_SCHEDULE=static,10\n");
    printf("Try things like: export OMP_SCHEDULE=dynamic,100\n");
    printf("Try things like: export OMP_SCHEDULE=guided,1000\n");
    printf("Try things like: export OMP_SCHEDULE=guided,1\n");
    printf("\nSchedule in effect: '%s'\n\n", getenv("OMP_SCHEDULE"));
    if (argc != 3)
        Usage(argv[0]);
    thread_count = strtol(argv[1], NULL, 10);
    n = strtol(argv[2], NULL, 10);
#ifdef DEBUG
    iterations = (int *)malloc((n + 1) * sizeof(int));
    starttime = (double *)malloc((n + 1) * sizeof(double));
    stoptime = (double *)malloc((n + 1) * sizeof(double));
#endif
    start = omp_get_wtime();
    global_result = Sum(n, thread_count);
    finish = omp_get_wtime();
    check = Check_sum(n, thread_count);
    error = fabs(global_result - check);
    printf("Result = %.14e\n", global_result);
    printf("Check = %.14e\n", check);
    printf("With n = %ld terms, the error is %.14e\n", n, error);
    printf("Elapsed time = %.3lf seconds\n", finish - start);
#ifdef DEBUG
    Print_iters(start, n);
    free(iterations);
#endif
    return 0;
} /* main */
/*--------------------------------------------------------------------
 * Function: Usage
 * Purpose: Print command line for function and terminate
 * In arg: prog_name
 */
void Usage(char *prog_name)
{
    fprintf(stderr, "usage: %s <number of threads> <number of terms>\n",
            prog_name);
    exit(0);
} /* Usage */
/*------------------------------------------------------------------
 * Function: f
 * Purpose: Compute value of function in which work is
 * proportional to the size of the first arg.
 * Input arg: i, n
 * Return val:
 */
double f(long i)
{
    long j;
    long start = i * (i + 1) / 2;
    long finish = start + i;
    double return_val = 0.0;
    for (j = start; j <= finish; j++)
    {
        return_val += sin(j);
    }
    return return_val;
} /* f */
/*------------------------------------------------------------------
 * Function: Sum
 * Purpose: Find the sum of the terms f(0), f(1), . . ., f(n),
 * where evaluating f requires work proportional to
 * its argument
 * Input args:
 * n: number of terms
 * thread_count: number of threads
 * Return val:
 * approx: f(0) + f(1) + . . . + f(n)
 */
double Sum(long n, int thread_count)
{
    double approx = 0.0;
    long i;
#pragma omp parallel for num_threads(thread_count) \
    reduction(+ : approx) schedule(runtime)
    for (i = 0; i <= n; i++)
    {
#ifdef DEBUG
        iterations[i] = omp_get_thread_num();
        starttime[i] = omp_get_wtime();
#endif
        approx += f(i);
#ifdef DEBUG
        stoptime[i] = omp_get_wtime();
#endif
    }
    return approx;
} /* Sum */
/*------------------------------------------------------------------
 */
double Check_sum(long n, int thread_count)
{
    long i;
    long finish = n * (n + 3) / 2;
    double check = 0.0;
#pragma omp parallel for num_threads(thread_count) default(none) shared(n, finish) private(i) \
    reduction(+ : check)
    for (i = 0; i <= finish; i++)
    {
        check += sin(i);
    }
    return check;
} /* Check_sum */
/*------------------------------------------------------------------
 * Function: Print_iters
 * Purpose: Print which thread was assigned which iteration.
 * Input args:
 * iterations: iterations[i] = thread assigned iteration i
 * n: size of iterations array
 */
void Print_iters(double start, long n)
{
    int i, start_iter, stop_iter, which_thread;
    double time1 = 0, time2 = 0, timee = 0;
    double threadtime[1000] = {0};
    printf("\n");
    printf("Thread\t\tIterations \tChunksize\tStarttime\tStoptime\tElapsed\
n");
    printf("------\t\t-----------------\t---------\t----------\t----------\
t----------\n");
    which_thread = iterations[0];
    start_iter = stop_iter = 0;
    for (i = 0; i <= n; i++)
    {
        if (iterations[i] == which_thread)
            stop_iter = i;
        else
        {
            time1 = starttime[start_iter] - start;
            time2 = stoptime[i - 1] - start;
            timee = time2 - time1;
            printf("%5d \t\t%6d -- %6d\t%d\t\t%.3lf\t\t%.3lf\t\t%.3lf\n",
                   which_thread, start_iter,
                   stop_iter, 1 + stop_iter - start_iter, time1, time2, timee);
            which_thread = iterations[i];
            threadtime[iterations[start_iter]] += timee;
            start_iter = stop_iter = i;
        }
    }
    time1 = starttime[start_iter] - start;
    time2 = stoptime[i - 1] - start;
    printf("%5d \t\t%6d -- %6d\t%d\t\t%.3lf\t\t%.3lf\t\t%.3lf\n", which_thread,
           start_iter,
           stop_iter, 1 + stop_iter - start_iter, time1, time2, time2 - time1);
    printf("\nThread\t\tTotal Time\n");
    printf("------\t\t------------\n");
    for (i = 0; i < thread_count; i++)
    {
        printf("%d\t\t%.3lf\n", i, threadtime[i]);
    }
} /* Print_iters */
