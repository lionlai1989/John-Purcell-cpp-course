#include <functional>
#include <iostream>

using namespace std;
using namespace placeholders;

int add(int a, int b, int c) {
    cout << a << ", " << b << ", " << c << endl;
    return a + b + c;
}

int run(function<int(int, int)> func) {
    /**
     * func is a function type which takes two integers as the input parameters and returns an
     * integer as the result.
     */
    return func(7, 3); // 7 and 3 are hardcode values.
}

class Test {
  private:
    int _sum;

  public:
    int add(int a, int b, int c) {
        cout << a << ", " << b << ", " << c << endl;
        _sum = a + b + c;
        return a + b + c;
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 bind.cpp && ./a.out
int main() {
    cout << add(1, 2, 3) << endl;
    // 1, 2, 3
    // 6

    /**
     * std:bind
     * The function template bind generates a forwarding call wrapper for f. Calling this wrapper is
     * equivalent to invoking f with some of its arguments bound to args.
     */
    auto calculate1 = bind(add, 3, 4, 5);
    cout << calculate1() << endl;
    // 3, 4, 5
    // 12

    /**
     * std::placeholders::_1, std::placeholders::_2, ..., std::placeholders::_N
     * The std::placeholders namespace contains the placeholder objects [_1, . . . _N] where N is an
     * implementation defined maximum number.
     * When used as an argument in a std::bind expression, the placeholder objects are stored in the
     * generated function object, and when that function object is invoked with unbound arguments,
     * each placeholder _N is replaced by the corresponding Nth unbound argument. 
     */
    auto calculate2 = bind(add, _1, _2, _3);
    cout << calculate2(10, 20, 30) << endl;
    // 10, 20, 30
    // 60

    auto calculate3 = bind(add, _2, _3, _1);
    cout << calculate3(10, 20, 30) << endl;
    // 20, 30, 10
    // 60

    auto calculate4 = bind(add, _2, 100, _1);
    cout << calculate4(10, 20) << endl;
    // 20, 100, 10
    // 130

    cout << run(calculate4) << endl;
    // 3 and 7 are hardcode values in run(). 100 is hardcode in calculate4().
    // 3, 100, 7
    // 110

    /**
     * We can also bind to a class' method. Firstly, we have to supply a pointer as the first
     * argument to the method. And the second argument here we actually need to make an object of
     * the class, Test, to bind to. So we actually need an object because the method, add(), in the
     * Test class could use instance variables of the class. E.g., we may want to know the
     * summation, _sum, of add(). And those are going to be different for every object, so we need
     * to tell bind which object we're actually binding to.
     */
    Test test;
    auto calculate5 = bind(&Test::add, test, _1, _2, _3);
    cout << calculate5(1, 2, 3) << endl;
    // 1, 2, 3
    // 6

    return 0;
}
