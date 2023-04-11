#include <iostream>
#include <typeinfo>

using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 decltype_and_typeid.cpp && ./a.out
int main() {
    int value1;                            // value1 is not initialize yet.
    cout << typeid(value1).name() << endl; // i

    double value2;
    cout << typeid(value2).name() << endl; // d

    string text;
    cout << typeid(text).name() << endl; // NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    // The output here is c++ name mangling.

    decltype(text) name = "Bob";         // decltype figures out the type of "text".
    cout << typeid(name).name() << endl; // NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    cout << name << endl;                // Bob

    return 0;
}
