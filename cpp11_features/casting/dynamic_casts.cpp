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

// Example command: g++ -Wall -std=c++11 -std=gnu++11 dynamic_casts.cpp && ./a.out
// NOTE: dynamic_cast only works if RTTI (run time type information) is turned on.
int main() {

    Parent parent;
    Brother brother;

    Parent *ppb1 = &parent;
    /**
     * It is dangerous to point a subclass pointer to a parent class object. static_cast will not
     * show any error.
     */
    Brother *pbb1 = static_cast<Brother *>(ppb1);

    Parent *ppb2 = &parent;
    Brother *pbb2 = dynamic_cast<Brother *>(ppb2);
    if (pbb2 == nullptr) {
        cout << "Invalid cast" << endl;
    } else {
        cout << pbb2 << endl;
    }
    /**
     * Basically it makes no sense to make ppb2 point to a parent object, so dynamic_cast returns
     * nullptr. This checking behaviour is perfomed in run-time. 
     * Output:
     * Invalid cast.
     */

    Parent *ppb3 = &brother;
    Brother *pbb3 = dynamic_cast<Brother *>(ppb3);
    if (pbb3 == nullptr) {
        cout << "Invalid cast" << endl;
    } else {
        cout << pbb3 << endl;
    }
    /**
     * It makes sense to make pbb3 point to a brother object.
     * Output:
     * 0x7ffefbda1510.
     */
    return 0;
}
