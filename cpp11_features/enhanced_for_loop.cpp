#include <iostream>
#include <vector>

using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 enhanced_for_loop.cpp && ./a.out
int main() {
    auto texts = {"one", "two", "three"};

    for (auto s : texts) {
        cout << s << endl;
    }
    // one
    // two
    // three

    vector<int> numbers;
    numbers.push_back(2);
    numbers.push_back(0);
    numbers.push_back(1);

    for (auto n : numbers) {
        cout << n << endl;
    }
    // 2
    // 0
    // 1

    string text = "hello";
    for (auto ch : text) {
        cout << ch << endl;
    }
    // h
    // e
    // l
    // l
    // o

    return 0;
}
