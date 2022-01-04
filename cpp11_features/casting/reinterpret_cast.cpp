#include <iostream>

using namespace std;

class Parent {
  public:
    virtual void speak() {
        cout << "Parent!" << endl;
    }
};

class Brother : public Parent {
};

class Sister : public Parent {
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 reinterpret_cast.cpp && ./a.out
int main() {

    Parent parent;
    Brother brother;
    Sister sister;

    Parent *pb = &brother;
    Sister *pbb = dynamic_cast<Sister *>(pb);
    if (pbb == nullptr) {
        cout << "Invalid cast" << endl;
    } else {
        cout << pbb << endl;
    }
    /**
     * dynamic_cast smartly figures out that it does not make any sense in run-time.
     * Output:
     * Invalid cast.
     */

    Sister *pbb1 = static_cast<Sister *>(pb);
    if (pbb1 == nullptr) {
        cout << "Invalid cast" << endl;
    } else {
        cout << pbb1 << endl;
    }
    /**
     * It will not crash but using static_cast is pretty stupid here. A Sister pointer points to a
     * brother object. We just want to demonstrate using static_cast is not really safe here.
     * Output:
     * 0x7ffe0f34f9d0
     */

    Sister *pbb2 = reinterpret_cast<Sister *>(pb);
    if (pbb2 == nullptr) {
        cout << "Invalid cast" << endl;
    } else {
        cout << pbb2 << endl;
    }
    /**
     * reinterpret_cast basically does even less checking than static_cast. It just literally does a
     * binary cast of one pointer type to another so it can pretty much kind of cast anything to
     * anything. 
     * Output:
     * 0x7ffe55421708
     */

    return 0;
}
