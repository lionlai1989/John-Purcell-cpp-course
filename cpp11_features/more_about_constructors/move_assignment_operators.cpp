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

    Test(Test &&other) {
        cout << "Move Constructor" << endl;
        _pBuffer = other._pBuffer;
        other._pBuffer = nullptr;
    }

    Test &operator=(const Test &other) {
        cout << "Assignment" << endl;
        _pBuffer = new int[SIZE]{};
        memcpy(_pBuffer, other._pBuffer, sizeof(int) * SIZE);
        return *this;
    }

    Test &operator=(Test &&other) {
        cout << "Move Assignment" << endl;

        /**
         * Here, the object, Test test1, to which we are assigning, already allocated memory. So, we
         * need to free up any memory that has been allocated.
         */
        delete[] _pBuffer;

        _pBuffer = other._pBuffer;

        other._pBuffer = nullptr; // Check the move constructor in move_constructors.cpp

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

// Example command: g++ -Wall -std=c++11 -std=gnu++11 move_assignment_operators.cpp && ./a.out
int main() {
    Test test1, test2; // Default No-Parameter Constructor

    test1 = get_test(); // Move Assignment

    test2 = test1; // Assignment

    return 0;
}
