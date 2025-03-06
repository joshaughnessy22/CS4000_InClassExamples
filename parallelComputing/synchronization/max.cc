
// This code figures out the maximum number of threads that
// make’s sense in C++ 11.
//
#include <iostream>
#include <thread>
using namespace std;
int main()
{
    int n;
    n = thread::hardware_concurrency(); //how many cores are on your computer 
    cout << "Maximum number of threads (concurrency) = "
         << n << endl;
}
