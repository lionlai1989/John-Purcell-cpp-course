#include <cstring>
#include <iostream>

using namespace std;

class Test {
  private:
    static const int SIZE = 100;

    int *_pBuffer;

  public:
    Test() {
        cout << "Default No-Parameter Constructor" << endl;
        _pBuffer = new int[SIZE]{};
        /**
         * Setting the default value to 0 is a good practice. Three different ways of setting the
         * memory to zero are shown here.
         * memset(_pBuffer, 0, sizeof(int) * SIZE);
         * _pBuffer = new int[SIZE]();
         * _pBuffer = new int[SIZE]{};
         */
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
        cout << "Copy Assignment Operator" << endl;
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

// Example command: g++ -Wall -std=c++11 -std=gnu++11 constructors_and_memory.cpp && ./a.out
int main() {
    Test test1 = get_test();
    cout << test1 << endl;
    // Default No-Parameter Constructor
    // Hello from test
    // Destructor

    return 0;
}
