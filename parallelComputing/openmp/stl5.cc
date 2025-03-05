
#include <iostream>
#include <set>
using namespace std;
int main() {
set<int> x;
for (int i=0;i<10000;i++) {
x.insert(i);
}
int errors = 0;
#pragma omp parallel for
for (int i=0;i<10000;i++) {
if (x.count(i)==0) {
#pragma omp atomic
errors++; // I inserted it, so this is an error!
}
}
cout << "Errors = " << errors << endl;
}
