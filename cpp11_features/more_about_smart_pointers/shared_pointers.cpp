#include <iostream>
#include <memory> // Smart pointers.

using namespace std;

class Test {
  public:
    Test() {
        cout << "Created" << endl;
    }

    void greet() {
        cout << "Hello" << endl;
    }

    ~Test() {
        cout << "Destroyed" << endl;
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 shared_pointers.cpp && ./a.out
int main() {
    shared_ptr<Test> p_test1(new Test());

    shared_ptr<Test> p_test2 = make_shared<Test>();

    shared_ptr<Test> p_test3 = p_test2;

    cout << "Finished" << endl;

    return 0;
}
