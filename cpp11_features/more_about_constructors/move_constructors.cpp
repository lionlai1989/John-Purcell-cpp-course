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
        /**
         * In the copy constructor, we have to allocate memory.
         * In the move constructor, we don't have to allocate any more memory. We just have to
         * change a couple of variables so it's very efficient.
         */
        _pBuffer = other._pBuffer;

        /**
         * NOTE: Here, the destructor of "other" will deallocate "_pBuffer" and we've stolen the
         * buffer so we don't want that to happen. So to deal with this all we have to do is set
         * "other._pBuffer" to point to nullptr. And it is safe to delete a nullptr.
         */
        other._pBuffer = nullptr;
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

// Example command: g++ -Wall -std=c++11 -std=gnu++11 move_constructors.cpp && ./a.out
int main() {
    vector<Test> test1;
    test1.push_back(Test());
    /**
     * It shows the move constructor is used here.
     * Output:
     * Default No-Parameter Constructor
     * Move Constructor
     * Destructor
     * Destructor
     */

    return 0;
}
