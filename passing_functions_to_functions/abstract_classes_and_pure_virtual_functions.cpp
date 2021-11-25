#include <iostream>

using namespace std;

class Animal {
    // We need a base class Animal, but it does not make sense to instantiate an Animal class.
  public:
    // This is not literally setting it equal to zero. This is just a notation that means there is
    // no implementation of this. This is what we call a pure virtual function/method and a class
    // which contains pure virtual functions/methods is called an abstract class. So Animal is an
    // abstract class because it has in this case just one pure virtual function.
    virtual void speak() = 0;

    virtual void run() = 0;
};

class Dog : public Animal {
    // In the real world, it makes sense to instantiate a Dog class.
  public:
    virtual void speak() {
        cout << "Woof!" << endl;
    }
};

class Labrador : public Dog {
  public:
    Labrador() {
        cout << "New Labrador" << endl;
    }
    virtual void run() {
        cout << "Labrador running" << endl;
    }
};

void test(Animal &a) {
    // a is a reference to an Animal object.
    // The good thing about this is that when we develop a function, we do not know what classes
    // will be passed as an argument here. We can just use the base class Animal here, and all the
    // subclasses of the Animal class can be passed in as an argument.
    a.run();
}

// Example command: g++ -Wall abstract_classes_and_pure_virtual_functions.cpp && ./a.out
int main() {
    // "Animal animal;": It does not work, because we cannot instantiate an abstract class.
    // "Dog dog;": It does not work, because run() is not implemented in the Dog class.
    Labrador labrador;
    labrador.run();   // Labrador running
    labrador.speak(); // Woof!

    // Animal animals[5]; It does not work because it cannot run the constructor of the Animal class.
    Labrador labs[5];
    // New Labrador
    // New Labrador
    // New Labrador
    // New Labrador
    // New Labrador

    // However, we could create an array of pointers which point to Animal objects. Now, the pointer
    // can point to the subclass of the Animal class.
    Animal *animals[5];
    animals[0] = &labrador; // "&labrador": the address of the concrete object, labrador.
    animals[0]->speak();    // Woof!

    test(labrador); // Labrador running

    return 0;
}
