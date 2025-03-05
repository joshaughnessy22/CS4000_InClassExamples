
#include <iostream>
using namespace std;
int main() {
int j=0;
// :-) there's a typo on the next line... see it?
#pragma parallel for
for (int i=0;i<10000;i++) {
j++;
}
}

/**
issue: will not compile due to a missing "omp" in the pragma message */
