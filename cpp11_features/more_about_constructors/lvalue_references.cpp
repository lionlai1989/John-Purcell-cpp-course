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

// Example command: g++ -Wall -std=c++11 -std=gnu++11 lvalue_references.cpp && ./a.out
int main() {
    Test test1 = get_test();
    cout << test1 << endl;

    Test &ref_test1 = test1;

    /**
     * NOTE: As described in lvalue_and_rvalue_references.cpp, we cannot bind a lvalue reference to
     * a rvalue like the following line. The return value of get_test() is a rvalue.
     * Test &ref_test2 = get_test();
     * 
     * BUT, what we can do is we can make "ref_test2" const, because constant lvalue references,
     * "ref_test2", can in fact bind to rvalues. Now what happens here is that we get the lifetime
     * of the rvalue, the return value from the function, get_test(), extended. So, as long as the
     * reference, "ref_test2" exists, the object that is returned from get_test() will continue to
     * exist. It is extended beyond the lifetime that it would normally have. Normally, it will be a
     * temporary variable, which as we saw in the previous tutorial, will be destroyed pretty
     * quickly as soon as it had served its purpose. But here it is going to hang around until it
     * gets to the closing curly braces of main(). 
     */
    const Test &ref_test2 = get_test();

    return 0;
}
