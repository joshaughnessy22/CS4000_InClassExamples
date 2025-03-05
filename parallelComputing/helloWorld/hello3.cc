
// A First Open MP Example
//
#include <omp.h>
#include <iostream>
using namespace std;
void Test() {
printf("Hello from thread %3d of %3d\n",
omp_get_thread_num(),omp_get_num_threads());
}
int main() {
#pragma omp parallel num_threads(20)
Test();
}

/**
issue: same as hello2

here, we can explicitly the number of threads we want the program to use*/