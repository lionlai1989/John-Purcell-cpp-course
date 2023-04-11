#include <iostream>
#include <vector>

using namespace std;

class Parent {
    // The variables of a class by default is private.
    int dogs;
    string text;

  public:
    /**
     * If the default constructor is commented out, and a constructor that takes a parameter is in
     * the parent class, we now lose the implicit default implementation of a no-parameter
     * constructor. 
     * Parent() {
     *     dogs = 5;
     *     cout << "No parameter parent constructor" << endl;
     * }
     */

    Parent(string text) {
        dogs = 5;
        this->text = text;
        cout << text << " string parent constructor" << endl;
    }
};
class Child : public Parent {
  public:
    /**
     * The default no-parameter constructor of the Parent class is commented out, so we have
     * to specify in child which constructor to run. 
     */
    Child() : Parent("Hello") {
    }
};

class Parent1 {
    int dogs;
    string text;

  public:
    /**
     *  In C++98, what we couldn't do is we couldn't call one constructor from another constructor
     *  within a class. But we can actually do this in C++11.
     *  NOTE: The important thing here is that to avoid calling recursion, because they will go
     *  round in a loop, each calling each other and that's just not going to work. I.e., we cannot
     *  do "Parent1(string text) : Parent1()" here.
     */
    Parent1() : Parent1("Hello") {
        dogs = 5;
        cout << "No parameter parent constructor" << endl;
    }
    Parent1(string text) {
        dogs = 5;
        this->text = text;
        cout << text << " string parent constructor" << endl;
    }
};
class Child1 : public Parent1 {
  public:
    Child1() {
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 delegating_constructors.cpp && ./a.out
int main() {
    Parent parent("World"); // World string parent constructor

    Child child; // Hello string parent constructor

    Parent1 parent1("World"); // World string parent constructor

    Child1 child1; // Hello string parent constructor
                   // No parameter parent constructor

    return 0;
}
