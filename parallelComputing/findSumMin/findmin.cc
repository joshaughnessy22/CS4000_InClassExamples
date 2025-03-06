
// Find the minimum of a set of numbers from a random vector
// Ostermann - Jan 26, 2023
//
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> vals;
    vals.resize(100000);
    srand(4000); // see the random number generator to always get same set
    for (int i = 0; i < (int)vals.size(); i++)
    {
        vals[i] = rand();
    }
    int min;
    min = vals[0];
    for (int i = 1; i < (int)vals.size(); i++)
    {
        if (min > vals[i])
        {
            min = vals[i];
        }
    }
    cout << "min = " << min << endl;
}
