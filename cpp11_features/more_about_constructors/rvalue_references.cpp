#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Test {
  private:
    static const int SIZE = 100;

    int *_pBuffer{nullptr};

  public:
    Test() {
        cout << "Default No-Parameter Constructor" << endl;
        _pBuffer = new int[SIZE]{};
    }

    Test(int i) {
        cout << "Parameterized Constructor" << endl;
        _pBuffer = new int[SIZE]{};
        for (int i = 0; i < SIZE; i++) {
            _pBuffer[i] = 7 * i;
        }
    }

    Test(const Test &other) {
        cout << "Copy Construtor" << endl;
        _pBuffer = new int[SIZE]{};
        memcpy(_pBuffer, other._pBuffer, sizeof(int) * SIZE);
    }

    Test &operator=(const Test &other) {
        cout << "Assignment" << endl;
        _pBuffer = new int[SIZE]{};
        memcpy(_pBuffer, other._pBuffer, sizeof(int) * SIZE);
        return *this;
    }

    ~Test() {
        cout << "Destructor" << endl;
        delete[] _pBuffer;
    }

    friend ostream &operator<<(ostream &out, const Test &test);
};

ostream &operator<<(ostream &out, const Test &test) {
    out << "Hello from test";
    return out;
}

Test get_test() {
    return Test();
}

void check(const Test &lvalue) {
    // lvalue takes a lvalue reference.
    cout << "lvalue function!" << endl;
}

void check(Test &&rvalue) {
    // rvalue takes a rvalue reference.
    cout << "rvalue function!" << endl;
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 rvalue_references.cpp && ./a.out
int main() {
    Test test1 = get_test();
    cout << test1 << endl;

    /**
     * ref_lvalue_test1 is a lvalue reference pointing to a rvalue.
     */
    Test &ref_lvalue_test1 = test1;

    /**
     * ref_rvalue_test2 is a lvalue reference which can bind to a rvalue. So we cannot bind
     * ref_rvalue_test2 to a lvalue like below. But we can bind ref_rvalue_test2 to a rvalue.
     * Test &&ref_rvalue_test2 = test1; // test1 is a lvalue here.
     */
    Test &&ref_rvalue_test2 = get_test();

    check(ref_lvalue_test1); // lvalue function!
    check(ref_rvalue_test2); // lvalue function!
    check(Test());           // rvalue function!
    check(get_test());       // rvalue function!

    return 0;
}
