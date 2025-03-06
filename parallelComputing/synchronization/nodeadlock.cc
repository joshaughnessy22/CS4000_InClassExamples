
#include <iostream>
#include <omp.h>
using namespace std;
// Four threads printing out the numbers 0 to 1000.
int main()
{
#pragma omp parallel for
    for (int i = 0; i < 1000; i++)
    {
        if (i % 2 == 0)
        {
#pragma omp critical
            {
                cout << i << endl;
            }
        }
        else
        {
#pragma omp critical
            {
                cout << i << endl;
            }
        }
    }
}
