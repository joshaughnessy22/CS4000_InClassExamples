/// Find the minimum of a set of numbers from a random vector
// Ostermann - Jan 26, 2023
//
#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;
// shared by all threads
vector<int> vals;
int min_val;
void find_min()
{ // Code executed by each thread:
    int mynum = omp_get_thread_num();
    int numthreads = omp_get_num_threads();
    int vsize = vals.size();
    int myshare = vsize / numthreads;
    int start, limit;
    // go from 'start' to 'limit'
    start = myshare * mynum;
    if ((mynum + 1) == numthreads)
    {
        limit = vsize;
    }
    else
    {
        limit = start + myshare;
    }
    for (int i = start; i < limit; ++i)
    {
        if (vals[i] < min_val)
        {
            sched_yield(); // make the problem more likely to occur
            min_val = vals[i];
        }
    }
}
int main(int argc, char *argv[])
{
    int numthreads = 20;
    if (argc == 2)
    {
        numthreads = atoi(argv[1]);
    }
    fprintf(stderr, "Requesting %d threads\n", numthreads);
    vals.resize(100000000);
    srand(4000); // see the random number generator to always get same set
    for (int i = 0; i < (int)vals.size(); i++)
    {
        vals[i] = rand();
    }
    // just timing code...
    chrono::time_point<chrono::system_clock> start;
    start = chrono::system_clock::now(); // Start the system clock.
    min_val = vals[0];
#pragma omp parallel num_threads(numthreads)
    find_min();
    // just timing code...
    chrono::time_point<chrono::system_clock> end;
    end = chrono::system_clock::now();
    chrono::duration<double> total_time = end - start;
    cerr << endl
         << "Base computation took " << total_time.count() << " seconds " << endl;
    cout << "min = " << min_val << endl;
}
