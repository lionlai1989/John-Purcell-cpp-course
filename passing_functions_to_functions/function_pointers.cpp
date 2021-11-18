#include <iostream>

using namespace std;

void test() {
    cout << "Hello" << endl;
}

// Example command: g++ -Wall function_pointers.cpp && ./a.out
int main() {
    // Call test() directly.
    test();

    void (*p_test)();

    p_test = &test;

    (*p_test)();

    return 0;
}
