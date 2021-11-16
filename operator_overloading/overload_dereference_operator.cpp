#include "Complex.h"
#include <iostream>

using namespace std;
using namespace caveofprogramming;

// g++ overload_dereference_operator.cpp Complex.cpp && ./a.out

int main() {
    Complex c1(2, 4);

    // Implement the conjugate of a complex number for the fun sake.
    cout << *c1 << endl;                  // (2,-4)
    cout << *c1 + *Complex(4, 3) << endl; // (6,-7)
    // Be careful of operator precedence. Because sometimes we overload some operators and stream
    // them together in expressions and find that they don't apply with the precedence that we
    // expect. Thus, usually it is nice to put () around the expression, (*c1) + (*Complex(4, 3))
    return 0;
}
