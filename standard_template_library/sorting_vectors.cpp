#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Test {
    int id;
    string name;

  public:
    Test(int id, string name) : id(id), name(name) {}
    void print() {
        cout << id << ": " << name << endl;
    }

    // less than operator "<" must be overloaded to make sort to work. If not, the error
    //     /usr/include/c++/9/bits/predefined_ops.h:90:22: error: no match for ‘operator<’ (operand types are ‘Test’ and ‘Test’)
    //    90 |       { return __val < *__it; }
    bool operator<(const Test &other) const {
        // It is sorted in the order of name.
        return name < other.name;

        // It is sorted in the order of id.
        return id < other.id;
    }

    // "sorting_vectors.cpp:31:23: error: ‘std::string Test::name’ is private within this context"
    // is shown. By default, the instance variable in a class is private whereas the struct is
    // public. friend means that if scanning down the Test class, the comp() is not seen yet, but
    // when it finds the function with prototype "bool comp(const Test &a, const Test &b)", we gonna
    // make it a friend, meaning it is allowed to access our private members.
    friend bool comp(const Test &a, const Test &b);
};

bool comp(const Test &a, const Test &b) {
    return a.name < b.name;
}

int main() {
    vector<Test> tests;

    tests.push_back(Test(3, "Vicky"));
    tests.push_back(Test(5, "Mike"));
    tests.push_back(Test(10, "Sue"));
    tests.push_back(Test(7, "Raj"));

    cout << "case 1" << endl;
    for (int i = 0; i < tests.size(); i++) {
        tests[i].print();
    }

    cout << "case 2" << endl;
    sort(tests.begin(), tests.begin() + 2, comp); // comp is a function pointer.
    for (int i = 0; i < tests.size(); i++) {
        tests[i].print();
    }

    cout << "case 3" << endl;
    sort(tests.begin(), tests.end(), comp);
    for (int i = 0; i < tests.size(); i++) {
        tests[i].print();
    }

    // Research on deque (double-ended queue).
    // deque.push_back()
    // deque.push_front()
    // deque.pop_back()
    // deque.pop_front()

    return 0;
}
