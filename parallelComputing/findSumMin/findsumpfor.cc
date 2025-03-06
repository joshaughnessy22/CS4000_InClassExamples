
// Find the sum
// This uses global variables -- let’s
// Find a better way to write it.
// Ostermann - Jan 26, 2023
#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
int debug = 1;
using namespace std;
int main(int argc, char *argv[])
{
    int numthreads = 4;
    vector<long long int> vals;
    long long int sum_g;
    if (argc == 2)
    {
        numthreads = atoi(argv[1]);
    }
    vals.resize(10000000);
    srand(4000); // see the random number generator to always get same set
    for (int i = 0; i < (int)vals.size(); i++)
    {
        vals[i] = rand();
    }
    fprintf(stderr, "Summing %d values using %d threads\n", (int)vals.size(),
            numthreads);
    // just timing code...
    chrono::time_point<chrono::system_clock> start;
    start = chrono::system_clock::now(); // Start the system clock.
    sum_g = 0;
#pragma omp parallel for num_threads(numthreads)
    for (int i = 0; i < (int)vals.size(); i++)
    {
        sum_g += vals[i]; // critical section not protected
    }
    // just timing code...
    chrono::time_point<chrono::system_clock> end;
    end = chrono::system_clock::now();
    chrono::duration<double> total_time = end - start;
    printf("Base computation took %.1f milliseconds\n", total_time.count() * 1000);
    cout << "sum = " << sum_g << endl;
    exit(0);
}
