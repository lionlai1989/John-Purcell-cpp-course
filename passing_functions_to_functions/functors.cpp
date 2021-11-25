#include <cassert>
#include <iostream>

using namespace std;

struct Test {
    // Test is now an abstract class.
    virtual bool operator()(string &text) = 0;
    virtual ~Test() {}
};

// A struct is used here, because a class by default all the methods and variables are private. However, a
// struct are public by default. So it is maybe just a little bit nicer in this particular case to
// use a struct.
struct MatchTest : public Test {
    // We overload the operator "()". The "()" operator can take a list of arguments.
    bool operator()(string &text) {
        // "bool operator()": it returns boolean.
        // "string &text":  a reference &text is an argument of the "()" operator.
        return text == "lion";
    }
};

struct AnotherMatchTest : public Test {
    // We overload the operator "()". The "()" operator can take a list of arguments.
    bool operator()(string &text) {
        // "bool operator()": it returns boolean.
        // "string &text":  a reference &text is an argument of the "()" operator.
        return text == "tiger";
    }
};

void check(string text, Test &predicate) {
    // "Test &predicate": predicate must be a reference if we want polymorphism to operate
    // correctly. Because if we want to pass in different kinds of Test classes. E.g., we can pass
    // in MatchTest or AnotherMatchTest when we call check(). That is why we need a reference here.
    // When we call "predicate(text)", it runs predicate's operator "()". Eg, if the passed in
    // functor is MatchTest, it runs MatchTest's operator "()". If the passed in functor is
    // AnotherMatchTest, it runs AnotherMatchTest's operator "()".
    if (predicate(text)) {
        cout << "Text matches" << endl;
    } else {
        cout << "No match" << endl;
    }
}

// Another nice example of demonstrating functors with internal states.
// This is a functor
struct add_x {
    add_x(int val) : x(val) {} // Constructor
    int operator()(int y) const { return x + y; }

  private:
    int x;
};

// Example command: g++ -Wall functors.cpp && ./a.out
int main() {
    // In C++, functor is another way of passing blocks of code to functions basically. There are
    // some things you can do with functors but you can't do it with function pointers. Function
    // pointers are more convenient for other situations. In C++11. We actually have lambda
    // expressions which are a form of syntactic sugar really for functors.

    MatchTest predicate; // predicate means something is testing something basically.

    string target_value = "lion";

    // "predicate(value)" looks like a function call but it is not. It is really a round bracket
    // operator "()" being applied using the object, predicate, to the value, target_value.
    cout << predicate(target_value) << endl;

    // The idea here is we could implement lots of different subclasses, MatchTest or
    // AnotherMatchTest, that all derive from the superclass, Test. Then we could pass the objects
    // (subclasses) to this function, check, here. The function, check, can take the reference of
    // the superclass, Test, as well as all the subclasses derived from the superclass.
    MatchTest m1;
    check("lion", m1);  // Text matches
    check("tiger", m1); // No match

    AnotherMatchTest m2;
    check("tiger", m2); // Text matches
    check("lion", m2);  // No match

    // Now you can use it like this:
    add_x add42(42);  // create an instance of the functor class
    int i = add42(8); // and "call" it
    assert(i == 50);  // and it added 42 to its argument
    // There are a couple of nice things about functors. One is that unlike regular functions, they
    // can contain state. The above example creates a function which adds 42 to whatever you give
    // it. But that value 42 is not hardcoded, it was specified as a constructor argument when we
    // created our functor instance. I could create another adder, which added 27, just by calling
    // the constructor with a different value. This makes them nicely customizable.

    return 0;
}
