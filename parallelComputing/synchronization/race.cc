
#include <iostream>
#include <thread>
using namespace std;
int sum_g=0;
void sum(int tid, int i, int j) {
for (int k=i; k<j;k++) {
sum_g+=k;
}
}
int main() {
thread tid1(sum,0,0,100);
thread tid2(sum,0,100,200);
thread tid3(sum,0,200,300);
thread tid4(sum,0,300,400);
tid1.join();
tid2.join();
tid3.join();
tid4.join();
cout << sum_g << endl;
}
