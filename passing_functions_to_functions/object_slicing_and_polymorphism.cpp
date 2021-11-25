#include <iostream>

using namespace std;

class Parent {
  private:
    int one;

  public:
    // We can define our own copy constructor in Parent class.
    Parent(const Parent &other) : one(0) {
        one = other.one;
        cout << "Copy parent" << endl;
    }

    // When we define our own copy constructor above, we lose the implicit no parameter constructor.
    // So we have to redefine that now for "Child c1;".
    Parent() : one(0) {
    }

    // If we add the keyword virtual here, C++ is going to create a table of function pointers that
    // point to the appropriate functions for the right type of object.
    virtual void print() {
        cout << "parent" << endl;
    }

    // A destructor is essential, if a virtual method is declared.
    virtual ~Parent() {
    }
};

class Child : public Parent {
  private:
    int two;

  public:
    // The private variable, one, in the Parent class cannot be initialized in the Child class here.
    Child() : two(0) {
    }

    void print() {
        cout << "child" << endl;
    }
};

// Example command: g++ -Wall object_slicing_and_polymorphism.cpp && ./a.out
int main() {
    // We call the following polymorphism where if you have a pointer (reference) to parent class
    // (superclass) type, then we can point the pointer to any instance of any subclass because the
    // subclasses is kind of one of the parent classes and then providing virtual methods in the
    // superclass. We can then call methods on the pointer and the right method will be invoked for
    // the actual particular kind of the object exactly as we got here.
    Child c1;
    Parent &p1 = c1; // p1 is just the reference.
    p1.print();      // child

    // It is the copy initialization. So if you declare a variable, p2, of some superclass type and when you
    // set it equal to some objects, Child(). We've got an equal sign (assignment operator) here,
    // that actually invokes the copy constructor. And it is invoking the implicit copy constructor
    // of the Parent class here, but we can see that working.
    // We try to create a Child class here. Subclasses have to run the constructors of
    // the parent classes in order to be instantiated. So when we define a subclass, we must either
    // have a default constructor in the parent class or else we must specify what constructor we
    // want to run in the parent class.
    // When we do "Parent p2 = Child();", the private variable of Child(), two, is sliced away
    // (object slicing), because when it is running Parent's copy constructor, it cannot possibly
    // know what variables subclasses have. Thus, the private variables of subclasses are thrown
    // away.
    Parent p2 = Child(); // It's running parent's copy constructor.
    p2.print();          // parent. It prints parent because p2 is an instance not a reference like "Parent &p1".

    return 0;
}
