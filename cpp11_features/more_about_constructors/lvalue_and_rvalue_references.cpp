#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Test {
  private:
    static const int SIZE = 100;

    int *_pBuffer;

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

// Example command: g++ -Wall -std=c++11 -std=gnu++11 lvalue_and_rvalue_references.cpp && ./a.out
int main() {
    /**
     * lvalue: value1
     * rvalue: 7
     */
    int value1 = 7;

    /**
     * In C++11, a lvalue is basically anything you can take the address of and we cannot take the
     * address of an rvalue. 
     * lvalue: value1
     * rvalue: 7
     * Therefore, "int *p_value1 = &7;" does not work, because 7 is a rvalue.
     */
    int *p_value1 = &value1;

    Test test1 = get_test();
    /**
     * The same principle applies with objects. test1 here is a rvalue, which is a value which we
     * can take take the address of. Also, the return values of functions are rvalues and rvalues
     * are often temporary values. 
     * Thus, "Test *p_test2 = &get_test();" does not work.
     */
    Test *p_test1 = &test1;

    /**
     * NOTE: "&++value1;" first increments the value of value1 by 1 and get the address of value1.
     * But, "int *p_value4 = &value1++;" does not work, because "value1++" is a rvalue
     */
    int *p_value3 = &++value1;
    cout << *p_value3 << endl; // 8

    /**
     * NOTE: Lastly,
     * "int *s = &(7 + value1);" does not work, because 7 is an rvalue, value1 is an lvalue, but 
     * (7 + value1) is an rvalue. 
     */
    return 0;
}
