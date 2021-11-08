#include <iostream>
#include <set>
using namespace std;

class Test {
    int id;
    string name;

  public:
    // The default constructor may not be necessary? But it is good to provide it anyway. It is good
    // practice.
    Test() : id(0), name("") {
    }

    Test(int id, string name) : id(id), name(name) {
    }

    void print() const {
        cout << id << ": " << name << endl;
    }

    // We need to overload the less than operator (<), otherwise the bolow error is shown. The set
    // object needs less than operator (<) to compare/sort elements.
    // stl_function.h:386:20: error: no match for ‘operator<’ (operand types are ‘const Test’ and ‘const Test’)
    // 386 |       { return __x < __y; }
    bool operator<(const Test &other) const {
        // other is the parameter sent into this operator< method.
        return name < other.name;
    }
};

int main() {
    // extraction or get from operator (>>)
    // insertion or put to operator (<<)

    // It only stores the elements that are unique.
    set<int> numbers;

    numbers.insert(3);
    numbers.insert(4);
    numbers.insert(1);
    numbers.insert(2);
    numbers.insert(1);

    for (set<int>::iterator it = numbers.begin(); it != numbers.end(); it++) {
        cout << *it << endl;
    }

    // Searches the container for an element equivalent to val and returns an iterator to it if
    // found, otherwise it returns an iterator to set::end.
    set<int>::iterator it_find = numbers.find(5);
    cout << "Found: " << *it_find << endl;
    // Found: 4 . It is wrong. There should not be elements found.

    it_find = numbers.find(3);
    cout << "Found: " << *it_find << endl;
    // Found: 3
    if (it_find != numbers.end()) {
        cout << "Found: " << *it_find << endl;
    }
    // Found: 3

    // Another way of checking if elements exist.
    if (numbers.count(10)) {
        cout << "Number found." << endl;
    }

    set<Test> tests;
    tests.insert(Test(10, "Mike"));
    tests.insert(Test(30, "Joe"));
    // Test(333, "Joe") will not be inserted into set because of the less than operator which only
    // compares the name. Thus, Test(30, "Joe") and Test(333, "Joe") are considered the same object.
    tests.insert(Test(333, "Joe"));
    tests.insert(Test(20, "Sue"));

    for (set<Test>::iterator it = tests.begin(); it != tests.end(); it++) {
        // We can not cout *it here, because we did not overload the put to (<<) operator.
        // cout << *it << endl;

        // We can also not use it->print() here. The iterator it here returns a const Test object that can
        // not be modified. But it does not know that whether print() method modifies the object or
        // not. So, print() must be a const.
        it->print();
    }

    return 0;
}
