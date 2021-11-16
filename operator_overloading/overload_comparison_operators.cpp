#include "Complex.h"
#include <iostream>

using namespace std;
using namespace caveofprogramming;

// g++ overload_comparison_operators.cpp Complex.cpp && ./a.out

int main() {
    Complex c1(3, 3);
    Complex c2(3, 3);

    if (c1 == c2) {
        cout << "Equal" << endl;
    } else {
        cout << "Not equal" << endl;
    }

    if (c1 != c2) {
        cout << "Not equal" << endl;
    } else {
        cout << "Equal" << endl;
    }
    return 0;
}
