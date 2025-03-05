
#include <iostream>
#include <thread>
using namespace std;
int total_sum[4]; // where each thread stores its result
// sum the numbers from i to j-1, store result in global array
void sum(int tid, int i, int j) {
thread::id my_id = this_thread::get_id();
int lsum=0;
for (int k=i; k<j; k++) {
lsum+=k;
}
total_sum[tid]= lsum;
cout << "Thread id = " << my_id << endl;
cout << std::dec << "Local sum = " << lsum << endl;
}
int main() {
thread tid1(sum,0,0,10);
thread tid2(sum,1,10,20);
thread tid3(sum,2,20,30);
thread tid4(sum,3,30,40);
tid1.join();
tid2.join();
tid3.join();
tid4.join();
// All the threads are done at this point!
int sum_t = 0;
for (int i=0;i<4;i++) {
sum_t+=total_sum[i];
}
cout << std::dec << "Total Sum = " << sum_t << endl;
{
// get the correct answer the old fashioned way
int csum = 0;
for (int k=0; k<40;k++) {
csum+=k;
}
cout << std::dec << "Double Check: Correct Sum = " << csum << endl;
}
}
