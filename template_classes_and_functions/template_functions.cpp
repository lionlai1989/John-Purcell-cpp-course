#include <iostream>

using namespace std;

// We want this function to print everything. Thus, we make it a template.
// template <class T>. Both class and typename work here.
template <typename T>
void print(T n) {
    cout << n << endl;
}

// Example command: g++ -Wall template_functions.cpp && ./a.out
int main() {
    print<string>("Hello"); // Hello
    print<int>(5);          // 5
    print("Hi there");      // Hi there

    return 0;
}
