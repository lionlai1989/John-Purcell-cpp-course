#include "Complex.h"
#include <iostream>

using namespace std;
using namespace caveofprogramming;

// g++ overload_plus.cpp Complex.cpp && ./a.out

int main() {
    Complex c1(3, 4);
    Complex c2(2, 3);
    Complex c3 = c1 + c2;
    cout << c1 << c2 << c3 << endl; // (3,4)(2,3)(5,7)
    cout << c1 + c2 + c3 << endl;   // (10,14)

    Complex c4(4, 2);
    Complex c5 = c4 + 7;
    cout << c5 << endl; // (11,2)

    Complex c6(1, 7);
    cout << 3.2 + c6 << endl; // (4.2,7)

    cout << 7 + c1 + c2 + 8 + 9 + c6 << endl; // (30,14)

    return 0;
}
