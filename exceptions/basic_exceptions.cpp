#include <exception>
#include <iostream>

using namespace std;

// compile command:
// g++ -v -Wall -fdiagnostics-color basic_exceptions.cpp && ./a.out

class MyException : public exception {
  public:
    // what() method in exception class is overwritten by me.
    virtual const char *what() const throw() {
        return "Something bad happened!";
    }
};

class Test {
  public:
    // can not use goes_wrong() throw(), because throw() with an empty bracket means it does not
    // throw any exceptions.
    void goes_wrong() {
        //
        throw MyException();
    }
};

void might_go_wrong() {
    bool error1 = false;
    bool error2 = true;

    // As soon as the first error is thrown, the function stops executing.
    if (error1) {
        throw "Something went wrong."; // It is a primitive string.
    }

    if (error2) {
        // Do not need to use new to create a string object.
        throw string("Something else went wrong.");
    }
}

void uses_might_go_wrong() {
    // Exception can be thrown out of uses_might_go_wrong().
    might_go_wrong();
}

class CanGoWrong {
  public:
    CanGoWrong() {
        char *memory = new char[999];
        delete[] memory;
    }
};

void goes_wrong() {
    bool error1_detected = true;
    bool error2_detected = false;

    if (error1_detected) {
        throw bad_alloc();
    }

    if (error2_detected) {
        throw exception();
    }
}

int main() {
    // Importance of catching order of exceptions. bad_alloc class is the subclasss of exception
    // class. Thus, bad_alloc exception is catched by (exception &e) instead of (bad_alloc &e).
    // Polymorphism. The subclass must be before its parent class. Otherwise, it is useless like
    // catch (bad_alloc &e) here.
    // The correct code is below.
    // } catch (bad_alloc &e) {
    //     cout << "Catching bad_alloc: " << e.what() << endl;
    // } catch (exception &e) {
    //     cout << "Catching exception: " << e.what() << endl;
    // }
    try {
        goes_wrong();
    } catch (exception &e) {
        cout << "Catching exception: " << e.what() << endl;
    } catch (bad_alloc &e) {
        cout << "Catching bad_alloc: " << e.what() << endl;
    }

    // Customize my own exception.
    Test test;
    try {
        test.goes_wrong();
    } catch (MyException &e) {
        cout << e.what() << endl;
    }

    // exception is thrown all the way out to main() through call stacks.
    try {
        uses_might_go_wrong();
    } catch (int e) {
        cout << "Error code:" << e << endl;
    } catch (char const *e) {
        cout << "Error message: " << e << endl;
    } catch (string &e) { // Use e or &e?
        cout << "string error message: " << e << endl;
    }

    // Use try/catch to catch exception while allocating memories.
    try {
        CanGoWrong wrong;
    } catch (bad_alloc &e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "Still running" << endl;

    return 0;
}
