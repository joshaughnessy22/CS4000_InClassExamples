
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#define ITERS 1000

int main()
{
    char *envir;
    vector<int> x;
    x.resize(ITERS);
    if ((envir = getenv("OMP_NUM_THREADS")) != NULL)
        printf("OMP_NUM_THREADS: %s\n",
               envir);
    if ((envir = getenv("OMP_SCHEDULE")) != NULL)
        printf("OMP_SCHEDULE: %s\n",
               envir);
    cout << "Making vector of " << ITERS << " random integers.\n";
#pragma omp parallel for
    for (int i = 0; i < ITERS; i++)
    {
        x[i] = rand();
    }
    // Let's count how many pairs (i,j) there are
    // such that x[i] > x[j]
    // This tell us how much the array is "unsorted"
    unsigned sum = 0;
#pragma omp parallel for schedule(runtime)
    for (int i = 0; i < ITERS; i++)
    {
        unsigned suml = 0;
        for (int j = i + 1; j < ITERS; j++)
        {
            if (x[i] > x[j])
            {
                suml++;
            }
        }
#pragma omp atomic
        sum += suml;
    }
    cout << "Unsorted Measure = " << sum << endl;
}
