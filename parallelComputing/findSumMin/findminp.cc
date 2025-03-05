
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
void find_min() { // Code executed by each thread:
int mynum = omp_get_thread_num();
int numthreads = omp_get_num_threads();
int vsize = vals.size();
int myshare = vsize/numthreads;
int start, limit;
// go from 'start' to 'limit'
start = myshare*mynum;
if ((mynum+1) == numthreads) {
limit = vsize;
} else {
limit = start + myshare;
}
for (int i=start; i<limit; ++i) {
if (vals[i] < min_val) {
pthread_yield_np(); // make the problem more likely to occur
min_val = vals[i];
}
}
}
int main(int argc, char *argv[]) {
// create the vector of random numbers
vals.resize(100000000);
srand(4000); // see the random number generator to always get same set
for (int i=0; i<(int)vals.size(); ++i) {
vals[i] = rand();
}
// find the minimum in parrallel
min_val = vals[0];
#pragma omp parallel num_threads(1000)
find_min();
cout << "min = " << min_val << endl;
}
