#include "Ring.h"
#include <iostream>
using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 ring_buffer.cpp && ./a.out
int main() {
    Ring<string> text_ring(3);
    text_ring.add("one");
    text_ring.add("two");
    text_ring.add("three");
    text_ring.add("four");
    text_ring.add("five");

    for (int i = 0; i < text_ring.size(); i++) {
        cout << text_ring.get(i) << endl;
    }
    // four
    // five
    // three

    return 0;
}
