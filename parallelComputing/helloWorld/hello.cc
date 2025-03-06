
// A First Open MP Example
//
#include <omp.h>
#include <iostream>
using namespace std;
void Test()
{
    cout << "Hello from thread " << omp_get_thread_num() << " nthreads "
         << omp_get_num_threads() << endl;
}
int main()
{
#pragma omp parallel
    Test();
}

/**
issue: cout is not threadsafe */