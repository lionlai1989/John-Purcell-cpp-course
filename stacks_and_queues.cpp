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

    // When a program reaches the end, the objects are deleted. Ergo, destructors are called.
    ~Test() {
        cout << "Objects destroyed" << endl;
    }

    void print() {
        cout << name << endl;
    }
};

int main() {
    // stack: LIFO
    cout << "stack: " << endl;
    stack<Test> test_stack;
    // Actually when we access the collection of objects (STL classes) stored in the test_stack,
    // usually the STL class will return a reference to the object that is in it.
    // In "Test test1 = test_stack.top();", test_stack.top() returns a reference to the object that
    // is in the stack, and becuase of the operator "=" and Test object test1, it actually copys the
    // object to which the reference refers into test1. So, it uses the default implementation
    // shallow copy/assignment operator "+" to copy the instance variable "string name;" into test1.
    // Ergo, that also means when we add "Test("Mike")" to a stack "test_stack", we gonna be destroying
    // the original object "Test("Mike")" that we added and a copy of "Test("Mike")" is copied into
    // the "test_stack". Thus, destructor is called when pushing Test objects into test_stack.
    test_stack.push(Test("Mike")); // cout << "Objects destroyed" << endl;
    test_stack.push(Test("Zion"));
    test_stack.push(Test("Sue"));
    Test test1 = test_stack.top();
    test1.print();

    test_stack.pop(); // destructor is called.
    test_stack.pop(); // destructor is called.

    // As above mentioned, copying objects is not efficient. We can use references "Test &test2"
    // here. So, now we do not have to make a copy of the returned object of test_stack.top()
    // anymore. test2 now is the reference to the existing object which is already in the stack.
    Test &test2 = test_stack.top();
    test2.print();

    // As above mentioned, test3 is now a reference to the object in the stack. Thus, the following
    // is really unreliable/invalid code. Because once an object is popped, the reference to the
    // object is invalidated. We can not rely on it anymore. If we want to use an object which is
    // popped, we need to copy the object like test1. It's done by the assignment operator "=".
    Test &test3 = test_stack.top();
    test_stack.pop();
    test3.print(); // Reference refers to destroyed objects.

    // Iterate through a stack.
    test_stack.push(Test("Vijay"));
    test_stack.push(Test("AJ"));
    test_stack.push(Test("Brennen"));
    while (test_stack.size() > 0) {
        Test &test = test_stack.top();
        test.print();
        test_stack.pop();
    }

    // queue: FIFO
    cout << "queue: " << endl;
    queue<Test> test_queue;
    test_queue.push(Test("Mike"));
    test_queue.push(Test("Zion"));
    test_queue.push(Test("Sue"));
    test_queue.back().print(); // The print() is the print() method of Test class.
    while (test_queue.size() > 0) {
        Test &test = test_queue.front();
        test.print();
        test_queue.pop();
    }

    return 0;
}
