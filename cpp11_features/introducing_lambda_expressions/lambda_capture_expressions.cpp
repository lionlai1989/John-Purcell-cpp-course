#include <iostream>

using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 lambda_capture_expressions.cpp && ./a.out
int main() {
    /**
     * A valid but useless lambda expression.
     */
    []() {}();

    int one = 1;
    int two = 2;
    int three = 3;

    // Capture one and two by value.
    [one, two]() { cout << one << ", " << two << endl; }(); // 1, 2

    // Caputure all local variables by value
    [=]() { cout << one << ", " << two << ", " << three << endl; }(); // 1, 2, 3

    // Caputure all local variables by value, but capture three by reference.
    [=, &three]() {
        cout << one << ", " << two << ", " << three << endl; // 1, 2, 3
        // two = 7; Throw "error: assignment of read-only variable ‘two’". Two is captured by value.
        three = 7;
        cout << one << ", " << two << ", " << three << endl; // 1, 2, 7
    }();

    // Default capture all local variables by reference.
    [&]() {
        cout << one << ", " << two << ", " << three << endl; // 1, 2, 7
        one = one + 1;
        two = two + 2;
        three = three + 3;
        cout << one << ", " << two << ", " << three << endl; // 2, 4, 10
    }();

    // Default capture all local variables by reference, but two and three by value.
    [&, two, three]() {
        cout << one << ", " << two << ", " << three << endl; // 2, 4, 10
        // two = two + 1; Throw "error: assignment of read-only variable ‘two’"
        one = one + 100;
        cout << one << ", " << two << ", " << three << endl; // 102, 4, 10
    }();
    return 0;
}
