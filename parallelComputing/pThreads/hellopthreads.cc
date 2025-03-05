
// Hello World with C/C++ Pthreads
// Based loosely off the
// program found on page 154 of the book
//
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <pthread.h>
using namespace std;
//
// This is the function that gets called once the thread is created.
// It possible to pass in more complicated arguments
// by using the generic pointer thread_num. //
void *hello_world(void *thread_num) {
// We passed in a long, but it was required to be
// treated as a pointer, so we cast back to a long.
long cur_thread = (long) thread_num;
cout << "Hello from thread " << cur_thread << endl;
return NULL;
}
int main(int argc, char *argv[]) {
pthread_t* thread_array;
int num_threads;
if (argc != 2) {
cout << "Expected one argument -- an integer for number of threads" << endl;
exit(-1);
}
// turn the only argument into an integer and check for failure
string argv1 = argv[1];
istringstream in(argv1);
in >> num_threads;
if (in.fail()) {
cout << "Error reading first argument";
cout << "-- should have been an integer" << endl;
exit(-1);
}
// create the threads
thread_array = new pthread_t[num_threads];
for (long i=0; i<num_threads; i++) {
pthread_create(
&thread_array[i], // store internal information about the thread
NULL, // NO thread attributes needed
hello_world, // what subroutine does the thread run
(void *)i); // what argument (pointer required) does the thread need
}
cout << "In the main thread" << endl;
// wait for the threads to finish
for (long i=0; i<num_threads; i++) {
pthread_join(
thread_array[i], // which thread to join
NULL); // the value the thread exited with (we don't care!)
cout << "Thread " << i << " is done " << endl;
}
// cleanup
delete [] thread_array; // not necessary in this program
exit(0);
}
