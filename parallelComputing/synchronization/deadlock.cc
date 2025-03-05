
// Two threads + named critical sections = deadlock
//
#include <iostream>
#include <omp.h>
using namespace std;
int main() {
#pragma omp parallel sections
{
#pragma omp section
{
#pragma omp critical (A)
{
cout << "Here in A -- first section " << endl;
#pragma omp critical (B)
{
cout << "Here in B --- first section " << endl;
}
}
}
#pragma omp section
{
#pragma omp critical (B)
{
cout << "Here in B -- second section " << endl;
#pragma omp critical (A)
{
cout << "Here in A --- second section " << endl;
}
}
}
}
}
