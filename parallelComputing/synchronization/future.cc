
#include <iostream>
#include <future> 
//used in conjunction with async to run tasks asynchronously and retrive their results once they are ready
//future is a class template that represents a future object
#include <thread>
//future and asnyc rely on underlying threading techniques
#include <cstdlib>
#include <unistd.h>
using namespace std;
int sum(int i, int j)
{
    sleep(5); // this makes the behavior more obvious
    cout << "Computing sum from " << i;
    cout << " to " << j << endl;
    int lsum = 0;
    for (int k = i; k < j; k++)
    {
        lsum += k;
    }
    return lsum;
}
int main()
{
    future<int> ans1 = async(sum, 0, 10);
    future<int> ans2 = async(sum, 10, 20);
    future<int> ans3 = async(sum, 20, 30);
    future<int> ans4 = async(sum, 30, 40);
    int sum = 0;
    sum += ans1.get();
    sum += ans2.get();
    sum += ans3.get();
    sum += ans4.get();
    cout << "Sum from 0 to 39 = " << sum << endl;
}
