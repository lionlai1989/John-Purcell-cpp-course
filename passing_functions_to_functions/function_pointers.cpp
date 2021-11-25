#include <iostream>

using namespace std;

void test() {
    cout << "Hello" << endl;
}

float multiply(int i1, float i2) {
    return i1 * i2;
}

// Example command: g++ -Wall function_pointers.cpp && ./a.out
int main() {
    // Function pointers are actually used even behind the scenes in c++. If you've been using
    // virtual methods, you've been using Function pointers implicitly already, because the virtual
    // keyword is an instruction to call c++ to create what we call a virtual table which is a table
    // of function pointers so that when you call a method in a child class via a pointer to the
    // parent class type. C++ can look up on a table of function pointers and find the right
    // function to call.
    test(); // Hello

    // We need some sort of pointer that can point to a function. In this case with a void return
    // type and with no parameters.
    // "void *p_test();": looks like a candidate which is a pointer, called p_test, pointing to a
    // function with void return type and with no parameters. BUT, it also looks like a function
    // that takes no parameters and has a return type of void pointer. So, this does not work. That
    // is why we need to put a parenthesis around "*p_test".
    void (*p_test)() = test;

    // Assign the addresss of test() to p_test. Both lines below work.
    p_test = &test;
    p_test = test;

    // Call the function via a pointer. Both lines below work.
    (*p_test)(); // Hello
    p_test();    // Hello

    float (*p_test1)(int, float) = multiply;
    cout << "World: " << p_test1(2, 3) << endl; // World: 6

    return 0;
}
