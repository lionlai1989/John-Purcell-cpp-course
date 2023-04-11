#include "Ring.h"
#include <iostream>
using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 iterable_classes.cpp && ./a.out
int main() {
    Ring<string> text_ring(3);
    text_ring.add("one");
    text_ring.add("two");
    text_ring.add("three");
    text_ring.add("four");
    text_ring.add("five");

    /**
     * If we make the 1st for loop work, then the 2nd for loop should also work automatically,
     * because we have implemented the syntax in which C++11 needs in the 1st for loop.
     */
    // C++98 style
    for (Ring<string>::iterator it = text_ring.begin(); it != text_ring.end(); it++) {
        cout << *it << endl;
    }
    // four
    // five
    // three

    text_ring.add("six");
    text_ring.add("seven");
    // C++11 style
    for (string value : text_ring) {
        cout << value << endl;
    }
    // seven
    // five
    // six

    return 0;
}
