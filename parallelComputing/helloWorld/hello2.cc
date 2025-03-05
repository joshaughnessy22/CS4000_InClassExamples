
// A First Open MP Example
//
#include <omp.h>
#include <iostream>
using namespace std;
void Test() {
printf("Hello from thread %d of %d\n",
omp_get_thread_num(),omp_get_num_threads());
}
int main() {
#pragma omp parallel
Test();
}

/**
issue: no issue, but it is impossible to predict which 
        threads will be output in what order */