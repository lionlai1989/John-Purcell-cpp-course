#include "Ring.h"
#include <iostream>
using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 nested_template_classes.cpp && ./a.out
int main() {
    Ring<int>::iterator it;

    it.print(); // Hello from iterator: 0

    /**
     * This is what a software architect should do. He knows about how things should look like
     * and just needs to construct the architecture of the program and let his subordinates
     * implement the detail. BUT, details should be well examined by the architect.
     * An example of Range-based for loop.
     * Ring<string> text_ring(3);
     * text_ring.add("one");
     * text_ring.add("two");
     * text_ring.add("three");
     * text_ring.add("four"); The size of text_ring is 3, so the 4th one will replace the 1st one.
     * text_ring.add("five"); The 5th one will replace the 2nd one.
     * 
     * for (int i = 0; i < text_ring.size(); i++) {
     *     cout << text_ring.get(i) << endl;
     * }
     * Output should be 
     * four
     * five
     * three
     */

    return 0;
}
