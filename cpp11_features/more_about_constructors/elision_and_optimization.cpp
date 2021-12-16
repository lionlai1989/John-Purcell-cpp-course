#include <iostream>

using namespace std;

class Test {
  public:
    Test() {
        cout << "Default No-Parameter Constructor" << endl;
    }

    Test(int i) {
        cout << "Parameterized Constructor" << endl;
    }

    Test(const Test &other) {
        cout << "Copy Construtor" << endl;
    }

    Test &operator=(const Test &other) {
        cout << "Assignment" << endl;
        return *this;
    }

    ~Test() {
        cout << "Destructor" << endl;
    }

    friend ostream &operator<<(ostream &out, const Test &test) {
        out << "Hello from test";
        return out;
    }
};

Test get_test() {
    return Test();
}

int main() {
    Test test1 = get_test();
    cout << test1 << endl;
    /** C++ deos return-value optimization.
     * Example command: g++ -Wall -std=c++11 -std=gnu++11 elision_and_optimization.cpp && ./a.out
     * Output: 
     * Default No-Parameter Constructor
     * Hello from test
     * Destructor
     */

    /** Turn off the optimization. Google "copy elision".
     * Example command: g++ -fno-elide-constructors -Wall -std=c++11 -std=gnu++11 elision_and_optimization.cpp && ./a.out
     * Output: 
     * Default No-Parameter Constructor
     * Copy Construtor
     * Destructor
     * Copy Construtor
     * Destructor
     * Hello from test
     * Destructor
     */

    return 0;
}
