
// Modificiation from previous example
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <pthread.h>
    using namespace std;
pthread_mutex_t mymutex;
pthread_mutex_t barrier_mutex;
int count;
int num_threads;
//
// This is the function that gets called once the thread is created.
// It possible to pass in more complicated arguments
// by using the generic pointer thread_num. //
void *hello_world(void *thread_num)
{
    long cur_val = (long)thread_num; // We passed in a long, but
    // it was treated as a pointer,
    // and then cast back to a long.
    pthread_mutex_lock(&mymutex);
    cout << "Hello from thread " << cur_val << endl;
    pthread_mutex_unlock(&mymutex);
    pthread_mutex_lock(&barrier_mutex);
    count++; // how many threads have gotten to this point?
    pthread_mutex_unlock(&barrier_mutex);
    while (count < num_threads)
        ; // Infinite loop?
    pthread_mutex_lock(&mymutex);
    cout << "Goodbye from Thread " << cur_val << endl;
    pthread_mutex_unlock(&mymutex);
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t *thread_array;
    if (argc != 2)
    {
        cerr << "Expected one argument -- an integer" << endl;
        exit(-1);
    }
    // read the numeric single argument
    string argv1 = argv[1];
    istringstream in(argv1);
    in >> num_threads;
    if (in.fail())
    {
        cout << "Error reading first argument -- should have been an integer" << endl;
        exit(-1);
    }
    // Create a critical section with default (NULL) attributes int return_code;
    pthread_mutex_init(&mymutex, NULL);
    pthread_mutex_init(&barrier_mutex, NULL);
    count = 0;
    thread_array = new pthread_t[num_threads];
    for (long i = 0; i < num_threads; i++)
    {
        pthread_create(&thread_array[i], NULL, hello_world, (void *)i);
    }
    pthread_mutex_destroy(&mymutex);
    for (long i = 0; i < num_threads; i++)
    {
        pthread_join(thread_array[i], NULL);
    }
    delete[] thread_array;
    exit(0);
}
