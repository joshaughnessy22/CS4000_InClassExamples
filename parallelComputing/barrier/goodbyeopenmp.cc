
#include <iostream>
#include <omp.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
omp_lock_t barrier_mutex;
sem_t mysemaphore;
int count = 0;
void Thread()
{
#pragma omp critical
    {
        cout << "Hello from thread " << omp_get_thread_num() << " nthreads "
             << omp_get_num_threads() << endl;
    }
    int num_threads = omp_get_num_threads();
    omp_set_lock(&barrier_mutex);
    count++;
    // cout << "I am thread " << count << " of " << num_threads << "\n";
    if (count == num_threads)
    {
        // Unlock all of the rest of the threads waiting to proceed
        omp_unset_lock(&barrier_mutex);
        // cout << "Waking everybody..."; usleep(250000); cout << "done\n";
        for (int i = 0; i < num_threads; i++)
        {
            sem_post(&mysemaphore);
        }
        sem_wait(&mysemaphore);
    }
    else
    {
        omp_unset_lock(&barrier_mutex);
        sem_wait(&mysemaphore);
    }
#pragma omp critical
    {
        cout << "Goodbye from thread " << omp_get_thread_num() << " nthreads "
             << omp_get_num_threads() << endl;
    }
}
int main()
{
    omp_init_lock(&barrier_mutex);
    sem_init(&mysemaphore, 0, 0);
    count = 0;
#pragma omp parallel
    Thread();
}
