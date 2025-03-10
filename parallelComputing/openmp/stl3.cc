
#include <iostream>
#include <set>
using namespace std;
int main()
{
    set<int> x;
    #pragma omp parallel for
    for (int i = 0; i < 10000; i++)
    {
        //#pragma omp atomic
        {
            x.insert(i); //atomic cannot be used 
        }
    }
    int errors = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (x.count(i) == 0)
        {
            errors++; // I inserted it, so this is an error!
        }
    }
    cout << "Errors = " << errors << endl;
}
