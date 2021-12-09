#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

class Test {
  private:
    int id = {3};
    string name = {"Mike"};

  public:
    Test() = default;

    Test(const Test &other) = default;
    Test &operator=(const Test &other) = default;

    Test(int id) : id(id) {
    }
    void print() {
        cout << id << ": " << name << endl;
    }
};

class AnotherTest {
  private:
    int id = {7};
    string name = {"John"};

  public:
    AnotherTest() = default;

    AnotherTest(const Test &other) = delete;
    AnotherTest &operator=(const Test &other) = delete;

    AnotherTest(int id) : id(id) {
    }
    void print() {
        cout << id << ": " << name << endl;
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 object_initialization.cpp && ./a.out
int main() {
    Test test;
    test.print();
    Test test1(77);
    test1.print();
    Test test2 = test1;
    test2 = test;

    AnotherTest another_test;
    another_test.print();
    AnotherTest another_test1(81);
    another_test1.print();
    /**
     * It won't work. We've deleted them in the class AnotherTest.
     * AnotherTest another_test2 = another_test1;
     * another_test2 = another_test;
     */
    return 0;
}
