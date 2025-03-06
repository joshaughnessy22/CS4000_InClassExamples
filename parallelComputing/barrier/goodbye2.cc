
#include <iostream>
#include <omp.h>
using namespace std;
void Thread()
{
#pragma omp critical
    {
        cout << "Hello from thread " << omp_get_thread_num() << " nthreads "
             << omp_get_num_threads() << endl;
    }
#pragma omp barrier
#pragma omp critical
    {
        cout << "Goodbye from thread " << omp_get_thread_num() << " nthreads "
             << omp_get_num_threads() << endl;
    }
}
int main()
{
#pragma omp parallel
    Thread();
}
