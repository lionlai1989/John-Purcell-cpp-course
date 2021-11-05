#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Test {
  private:
    string name;

  public:
    // constructor
    Test(string name) : name(name) {
    }

    // Destructor
    ~Test() {
        cout << "Objects destroyed" << endl;
    }

    void print() {
        cout << name << endl;
    }
};

int main() {
    // last in first out
    stack<Test> test_stack;

    test_stack.push(Test("Mike"));
    test_stack.push(Test("Zion"));
    test_stack.push(Test("Sue"));

    Test test1 = test_stack.top();
    test1.print();

    test_stack.pop();
    Test test2 = test_stack.top();
    test2.print();

    // first in first out
    queue<Test> test_queue;

    return 0;
}
