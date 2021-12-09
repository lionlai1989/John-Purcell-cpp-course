#include <iostream>

using namespace std;

void test_greet(void (*greet)(string)) {
    // greet is a function pointer.
    greet("Bob");
}

void run_divide(double (*divide)(double a, double b)) {
    auto rval = divide(9, 3);
    cout << rval << endl;
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 lambda_parameters_and_return_type.cpp && ./a.out
int main() {
    auto pGreet = [](string name) { cout << "Hello " << name << endl; };

    pGreet("Mike");     // Hello Mike
    test_greet(pGreet); // Hello Bob

    /**
     * A lambda expression that returns a double. Here, trailing return type syntax "-> double" is
     * used because there are two return statements, "return 0" and "return a / b". And C++ cannot
     * infer the return type, we have to explicitly specify the return type. 
     */
    auto pDivide = [](double a, double b) -> double {
        if (b == 0.0) {
            return 0;
        }
        return a / b;
    };

    cout << pDivide(10.0, 5.0) << endl; // 2
    cout << pDivide(10.0, 0) << endl;   // 0
    run_divide(pDivide);                // 3

    return 0;
}
