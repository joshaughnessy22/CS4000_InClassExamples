
// Implementing barriers with a counter and // a mutex and a semaphore!
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h> // For O_CREAT 
//a new file or semaphore should be created if it does not already exist
//when used with sem_open is tells the function to create a new semaphore if not exist
#include <unistd.h> // For S_IRUSR and S_IWUSR
// S_IRUSR and S_IWUSR are the read and write permissions for the user
//
    using namespace std;


pthread_mutex_t mymutex;
pthread_mutex_t print_mutex;
pthread_mutex_t barrier_mutex;
sem_t *my_semaphore;
int count;
int num_threads;
// This is the function that gets called once the thread is created.
// It possible to pass in more complicated arguments
// by using the generic pointer thread_num. //
void *hello_world(void *thread_num)
{
    long cur_val = (long)thread_num; // We passed in a long, but
    // it was treated as a pointer,
    // and then cast back to a long.
    pthread_mutex_lock(&print_mutex);
    cout << "Hello from thread " << cur_val << endl;
    pthread_mutex_unlock(&print_mutex);
    pthread_mutex_lock(&barrier_mutex);
    ++count;
    if (count == num_threads)
    {
        // Unlock all of the rest of the threads waiting to proceed
        pthread_mutex_unlock(&barrier_mutex);
        for (int i = 0; i < num_threads; i++)
        {
            sem_post(my_semaphore);
        }
        sem_wait(my_semaphore);
    }
    else
    {
        pthread_mutex_unlock(&barrier_mutex);
        if (sem_wait(my_semaphore) != 0)
            perror("sem_wait()");
    }
    pthread_mutex_lock(&print_mutex);
    cout << "Goodbye from thread " << cur_val << endl;
    pthread_mutex_unlock(&print_mutex);
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t *thread_array;
    if (argc > 1)
    {
        string argv1 = argv[1];
        istringstream in(argv1);
        in >> num_threads;
        if (in.fail())
        {
            cout << "Error reading first argument -- should have been an integer" << endl;
            exit(-1);
        }
    }
    else
    {
        cout << "Expected one argument -- an integer" << endl;
        exit(-1);
    }
    // Create a critical section with default (NULL) attributes
    pthread_mutex_init(&mymutex, NULL);
    pthread_mutex_init(&print_mutex, NULL);
    pthread_mutex_init(&barrier_mutex, NULL);
    // switched to Posix Named Semaphores for portability
    if ((my_semaphore = sem_open("sem", O_CREAT, S_IRUSR | S_IWUSR, 0)) ==
        SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }
    // The first 0 indictates that the semaphore will be shared among threads
    // as opposed to processes --- the second gives the
    // initial value.
    count = 0;
    thread_array = new pthread_t[num_threads];
    for (long i = 0; i < num_threads; i++)
    {
        pthread_create(&thread_array[i], NULL, hello_world, (void *)i);
    }
    pthread_mutex_destroy(&mymutex); // Probably want to check
    // this
    for (long i = 0; i < num_threads; i++)
    {
        pthread_join(thread_array[i], NULL);
    }
    delete[] thread_array;
    return 0;
}
