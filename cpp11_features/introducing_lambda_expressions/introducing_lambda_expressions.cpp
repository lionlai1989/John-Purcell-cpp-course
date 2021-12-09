#include <iostream>

using namespace std;

void test(void (*pFunc)()) {
    // pFunc is a function pointer which points to a function that returns void returned type.
    pFunc();
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 introducing_lambda_expressions.cpp && ./a.out
int main() {
    /**
     * Various lambda expressions.
     */
    []() { cout << "0: Hello" << endl; }(); // 0: Hello

    auto func = []() { cout << "1: Hello" << endl; };

    func();     // 1: Hello
    test(func); // 1: Hello

    test([]() { cout << "2: Hello" << endl; }); // 2: Hello

    return 0;
}
