#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

class Test {
  public:
    Test(initializer_list<string> texts) {
        for (auto value : texts) {
            cout << value << endl;
        }
    }

    void print(initializer_list<string> texts) {
        for (auto value : texts) {
            cout << value << endl;
        }
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 initializer_lists.cpp && ./a.out
int main() {
    vector<int> numbers = {1, 3, 4, 5};
    cout << numbers[2] << endl; // 4

    Test test = {"apple", "orange", "banana"};
    // apple
    // orange
    // banana

    test.print({"one", "two", "three", "four"});
    // one
    // two
    // three
    // four

    return 0;
}
