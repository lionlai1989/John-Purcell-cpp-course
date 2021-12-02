#include <iostream>
#include <vector>
using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 c++11_initialization.cpp && ./a.out
int main() {
    /**
     * {}: Braces
     * []: Brackets
     * (): Parentheses
     */
    int value{5};
    cout << value << endl; // 5

    string text{"Hello"};
    cout << text << endl; // Hello

    int numbers[]{1, 2, 4};
    cout << numbers[1] << endl; // 2

    //int *p_ints = new int[]{1,2,3}; This won't work.
    int *p_ints = new int[3]{1, 2, 3};
    cout << *p_ints << endl; // 1
    delete p_ints;

    int value1{};
    cout << value1 << endl; // 0

    int *p_something{&value};
    cout << *p_something << endl; // 5

    int *p_something1{};
    cout << p_something1 << endl; // 0

    int *p_something2{nullptr};   // equivalent to *p_something2 = nullptr
    cout << p_something2 << endl; // 0

    int numbers1[5]{};
    cout << numbers1[1] << endl; // 0

    struct {
        int value;
        string text;
    } s1 = {5, "hi"};
    cout << s1.text << endl; // hi

    vector<string> strings = {"My ",
                              "name ",
                              "is ",
                              "Handsome."};
    cout << strings[3] << endl; // Handsome.

    return 0;
}
