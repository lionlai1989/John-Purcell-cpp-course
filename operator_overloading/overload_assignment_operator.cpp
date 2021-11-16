#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Test {
  private:
    int id;
    string name;

  public:
    Test() : id(0), name("") {
    }
    Test(int id, string name) : id(id), name(name) {
    }

    ~Test() {
    }

    void print() {
        cout << id << ": " << name << endl;
    }

    // const Test &: It will be very strange that if "test3 = test2 = test1;" changes the test2 object. So, it
    // returns a const reference.
    // const Test &other: "test2 = test1;" will not change the test1 object. We use references
    // because it is more efficient to pass in an object instead of copying it.
    const Test &operator=(const Test &other) {
        cout << "Assignment running." << endl;
        // It is the actual code to overwrite operator. So, when running "test2 = test1;", it runs
        // the code here.
        id = other.id - 1;
        name = other.name;

        // dereference the actual object, this,  passed into. The return type is a const reference,
        // which means that "*this" is a reference.
        return *this;
    }

    Test(const Test &other) {
        cout << "Copy constructor running." << endl;
        id = other.id;
        name = other.name;

        // *this = other; would also work.
    }
};

int main() {
    Test test1(10, "Mike");
    test1.print(); // 10: Mike

    Test test2(20, "Bob");
    // c++ provides a default implementation to make assignment operator "=" to work. It shallow
    // copys the value of variables in test1 to test2. However, sometimes we want a deep copy. In
    // another word, we want to copy in a way that makes sense to what variables present. Eg, if an
    // id for every object must be unique, the id in test2 shall not be the same as test1. Eg, if
    // there is a pointer in test1, which points to the allocated memory, and we shallow copy test1
    // to test2, and now we have a pointer in test2 points at the same memory as test1 allocated,
    // rather than allocating your own in test1. Hence, sometimes we want to overwrite the
    // assignment operator "=".
    // "test2 = test1;" can be seen as calling a method on test2, and providing with an argument,
    // test1. Also, "=" can be seen as having two arguments, test1 and test2. If we implement a
    // method and call it on test2, and pass test1, there are actually two arguments, test1 and an
    // implicit first argument, which is a reference to the object that being called on. And it
    // makes us to use "this" operator in our method. Eg, "test2.print();" seems to have no argument,
    // but there is actually an implicit first argument, the object itself.
    test2 = test1;
    test2.print(); // Assignment running. 9: Mike

    Test test3;
    // It can be seen as calling a method on test2, and passing in test1 as argument, and returning
    // a referece pointing to test2. And test3 takes the reference which points to test2 as
    // argument. In another word, the returned value of equals operator has to a reference to the
    // object that is being called on.
    //test3 = test2 = test1;

    // "test3 = test2;"" is equivalent to "test3.operator=(test2);"
    test3.operator=(test2);
    test3.print(); // Assignment running. 8: Mike

    cout << endl;

    // Copy initialization. There is no "Assignment running." here (assignment operator does not
    // work here), because there is an implicit copy constructor doing this. We can overwrite the
    // implicit copy constructor like above.
    Test test4 = test1;
    test4.print(); // Copy constructor running. 10: Mike

    // NOTE: There is something called the Rule of Three in c++. If you define any one of a copy
    // construtor, an assignment operator, or a destructor, you need to implement the other two as
    // well.
    return 0;
}
