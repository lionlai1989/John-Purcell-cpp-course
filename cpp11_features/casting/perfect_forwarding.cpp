#include <iostream>

using namespace std;

class Test {
};

template <typename T>
void call1(T &&arg) {
    /**
     * If the input argument is a lvalue, the program will still work and arg will become a lvalue
     * reference. Eventually, it will call the lvalue version of check function.
     * NOTE: If the arg is a rvlaue, the lvalue version of check function is still being called,
     * because "arg" looks like a lvalue reference, so the lvalue version of check function will be
     * called anyway.
     */
    check(arg);
}

template <typename T>
void call2(T &&arg) {
    // Perfect forwarding.
    check(static_cast<T>(arg));
}

template <typename T>
void call3(T &&arg) {
    // Better: forward can be used here to implement perfect forwarding like static_cast.
    check(forward<T>(arg));
}

void check(Test &lvalue) {
    // lvalue takes a lvalue reference.
    cout << "lvalue function!" << endl;
}

void check(Test &&rvalue) {
    // rvalue takes a rvalue reference.
    cout << "rvalue function!" << endl;
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 perfect_forwarding.cpp && ./a.out
int main() {
    Test test; // test is a lvalue.

    auto &&t1 = Test();

    /**
     * Actually we should not be able to bind t2 to a lvalue. However, in fact there is a rule in C++11,
     * it says if the auto boiled down to a lvalue reference type, then the reference as a whole
     * would collapse. What would be left with would be an lvalue reference which is why t2 can
     * bind to an lvalue. So this is one of the reference collapsing rules for C++11.
     * NOTE: Google reference collaping in C++.
     */
    auto &&t2 = test;

    /**
     * Now the idea behind perfect forwarding is that we want to call the right version of a
     * function depending on whether we passed a rvalue or lvalue to our template function. As we
     * see in the above example, t2 can bind to a lvalue reference. So, call1 can also take either
     * rvalue or lvalue as an input parameter even though "arg" in "call1(T &&arg)" is a rvalue reference.
     * 
     * Here, something unnatural happens. Test() returns a rvalue, but it runs the version of lvalue
     * check function in the end. Perfect forwarding is not working here.
     * Output:
     * lvalue function!
     * lvalue function!
     */
    call1(Test()); // Test() returns a rvalue.
    call1(test);   // test is a lvalue.

    /**
     * Here, perfect forwarding is working. The correct check function is being called for each case.
     * Output:
     * rvalue function!
     * lvalue function!
     * rvalue function!
     * lvalue function!
     */
    call2(Test()); // Test() returns a rvalue.
    call2(test);   // test is a lvalue.
    call3(Test()); // Test() returns a rvalue.
    call3(test);   // test is a lvalue.

    return 0;
}
