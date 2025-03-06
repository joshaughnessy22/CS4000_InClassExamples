
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#define ITERS 1000

int main()
{
    vector<int> x;
    x.resize(ITERS);
    cout << "Making vector of " << ITERS << " random integers.\n";
#pragma omp parallel for
    for (int i = 0; i < ITERS; i++)
    {
        x[i] = rand(); //random number generator IS NOT threadsafe
    }
    // Let's count how many pairs (i,j) there are
    // such that x[i] > x[j]
    // This tell us how much the array is "unsorted"
    unsigned sum = 0;
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = i + 1; j < ITERS; j++)
        {
            if (x[i] > x[j])
            {
                sum++; //critical section is not threadsafe either
            }
        }
    }
    cout << "Unsorted Measure = " << sum << endl;
}
