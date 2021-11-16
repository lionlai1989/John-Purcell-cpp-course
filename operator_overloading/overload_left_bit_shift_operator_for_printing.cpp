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

    const Test &operator=(const Test &other) {
        id = other.id;
        name = other.name;

        return *this;
    }

    Test(const Test &other) {
        *this = other;
    }

    // Normally this function is put into the different cpp file. It is here for the sake of
    // demonstration purpose.
    friend ostream &operator<<(ostream &out, const Test &test) {
        out << test.id << ": " << test.name;
        return out;
    }
};

int main() {
    Test test1(10, "Mike");
    Test test2(20, "Bob");
    test1.print();

    // It would be nice to use cout. Then we need to overload "<<". "<<" has left-right associativity.
    cout << test1 << test2 << endl; // (cout << test1) << test2 << endl;

    // "+" has right-left associativity.
    int i = 1 + 2 + 5; // == i = (1 + (2 + 5))

    return 0;
}
