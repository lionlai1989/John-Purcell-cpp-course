#include <iostream>

using namespace std;

template <typename T>
void print(T n) {
    cout << "Template version: " << n << endl;
}

// We can have two functions with identical name as long as the argument list of these two functions
// are different.
void print(int value) {
    cout << "Non-template version: " << value << endl;
}

template <typename T>
void show() {
    cout << T() << endl;
}

// Example command: g++ -Wall template_functions_and_type_inference.cpp && ./a.out
int main() {
    print<string>("Hello"); // Template version: Hello
    print<int>(5);          // Template version: 5
    print("Hi there");      // Template version: Hi there

    // c++ looks at the argument list to infer/deduce the correct funtion to use.
    print(6);      // Non-template version: 6
    print<>(7);    // Template version: 7
    print<int>(8); // Template version: 8

    // The three lines below cannot be compiled. -> "couldn’t deduce template parameter ‘T’"
    // The reason is that c++ can not infer the type. The argument list of show() is empty.
    // show();
    // show<>();
    // show(5);

    show<double>(); // 0

    return 0;
}
