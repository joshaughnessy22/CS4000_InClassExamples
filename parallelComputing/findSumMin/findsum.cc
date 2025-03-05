
Page
1
of 2
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
// Global variables
vector<long long int> vals;
long long int sum_g;
void find_sum() {
int a = omp_get_thread_num();
int b = omp_get_num_threads();
int n = vals.size();
int limit; // go from here
if ((a+1) == b) {
limit = n;
} else {
limit = (n/b)*(a+1);
}
long long int sum_l = 0;
for (int i=(n/b)*a; i<limit;i++) {
sum_l+=vals[i];
}
#pragma omp critical
sum_g+=sum_l;
}
int main(int argc, char *argv[]) {
int numthreads = 4;
if (argc == 2) {
numthreads = atoi(argv[1]);
}
fprintf(stderr,"Requesting %d threads\n", numthreads);
vals.resize(10000000);
srand(4000); // see the random number generator to always get same set
for (int i=0; i<(int)vals.size(); i++) {
vals[i] = rand();
}
fprintf(stderr,"Summing %d values using %d threads\n", (int)vals.size(),
numthreads);
// just timing code...
chrono::time_point<chrono::system_clock> start;
start = chrono::system_clock::now(); // Start the system clock.
sum_g = 0; //Compute the sum
#pragma omp parallel num_threads(numthreads)
find_sum();
// just timing code...
chrono::time_point<chrono::system_clock> end;
end = chrono::system_clock::now();
chrono::duration<double> total_time = end - start;
printf("Base computation took %.1f milliseconds\n", total_time.count()*1000);
cout << "sum = " << sum_g << endl;
exit(0);
}
