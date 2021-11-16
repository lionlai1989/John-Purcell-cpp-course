#include "Complex.h"
#include <iostream>

using namespace std;
using namespace caveofprogramming;

// g++ complex_number_class.cpp Complex.cpp && ./a.out

int main() {
    Complex c1;
    Complex c2(2, 3);
    Complex c3 = c2;

    c1 = c2;

    cout << c2 << " " << c3 << endl;

    return 0;
}
