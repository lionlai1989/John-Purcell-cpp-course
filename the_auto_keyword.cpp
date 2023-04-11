#include <iostream>
#include <typeinfo>

using namespace std;

template <class T, class K>
auto test(T value1, K value2) -> decltype(value1 + value2) {
    return value1 + value2;
}

int get() {
    return 999;
}

auto test2() -> decltype(get()) {
    return get();
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 the_auto_keyword.cpp && ./a.out
int main() {
    // auto will look at what you initialize a variable with and in effect declares type for you.
    auto value = 7;
    auto text = "Hello"; // text is a primitive string.

    cout << value << " " << text << endl; // 7 Hello

    cout << test(1, 2) << endl; // 3

    cout << test2() << endl; // 999

    return 0;
}
