
#include <iostream>
#include <future>
#include <thread>
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
    /**
     * std::launch::async: The function is executed in a new thread.
       std::launch::deferred: The function is executed only when future::get() or 
       future::wait() is called on the returned std::future object,
                and it will be executed in the calling thread.
       std::launch::async | std::launch::deferred: The implementation chooses whether
                to execute the function asynchronously or defer it. This is the default behavior 
                if no launch policy is specified.
     */
    future<int> ans1 = async(launch::async, sum, 0, 10);
    future<int> ans2 = async(launch::async, sum, 10, 20);
    future<int> ans3 = async(launch::async, sum, 20, 30);
    future<int> ans4 = async(launch::deferred, sum, 30, 40); 
    int sum;
    sum = 0;
    sum += ans1.get(); 
    sum += ans2.get(); 
    sum += ans3.get();
    sum += ans4.get();
    cout << "Sum from 0 to 39 = " << sum << endl;
}
