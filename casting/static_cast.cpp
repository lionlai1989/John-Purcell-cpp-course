#include <iostream>

using namespace std;

class Parent {
  public:
    void speak() {
        cout << "Parent!" << endl;
    }
};

class Brother : public Parent {
};

class Sister : public Parent {
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 static_cast.cpp && ./a.out
int main() {
    float value = 3.23;
    cout << (int)value << " " << int(value) << endl;
    cout << static_cast<int>(value) << endl; // "<int>" is the type which it wants to cast to.

    Parent parent;
    Brother brother;

    Parent *pp = &brother;        // A parent class pointer which points to an address of a subclass object.
    cout << "pp  " << pp << endl; // pp  0x7ffef78d5192

    /**
     * The code below will not work because it does not really make sense.
     * Brother *pb = &parent;
     * To make it work, we have to cast (force) the parent address to the subclass address. 
     * However, it is very unsafe because we could just have some methods in Brother which do not
     * exist in the parent. And then we can try to call them using this point in time the program
     * would just crash. 
     */
    Brother *pb = static_cast<Brother *>(&parent);
    cout << "pb  " << pb << endl; // pb  0x7ffef78d5191

    Parent *ppb = &brother;
    cout << "ppb " << ppb << endl; // ppb 0x7ffef78d5192
    // Brother *pbb = ppb; This line does not work, but we can force it to work like below.

    /**
     * It is potentially very error prone because what static_cast does is purely a compile time
     * thing. So there's no runtime checking. For example, the pointer, pbb, could point to a parent
     * object and not a brother object. So it could turn out later in our code that this is
     * actually invalid. pbb might start calling the methods which don't exist in the parent. And
     * we might have the pointer, ppb, pointing at a parent object. So the method calls will fail or
     * at least not do what we expect them to do. 
     */
    Brother *pbb = static_cast<Brother *>(ppb);
    cout << "pbb " << pbb << endl; // pbb 0x7ffef78d5192

    Parent &&rvalue_ref1 = Parent(); // Parent() returns a rvalue.
    // Parent &&rvalue_ref = parent; This line do not work, because parent is a lvalue.
    Parent &&rvalue_ref2 = static_cast<Parent &&>(parent); // Cast to a rvalue reference.
    rvalue_ref2.speak();                                   // Parent!

    return 0;
}
