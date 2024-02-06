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
    void throw_unknown_exception() {
        /**
         * Notice that Divide by zero is undefined behaviour, and undefined behaviour is
         * NOT exceptional behaviour (in any language). If my code has undefined
         * behaviour then my entire program is invalid. There is NOTHING I can do to
         * save my program. Even with `catch (...)` and `throw`, my program still crashes.
         * 
         * Fortunately, it outputs the following message:
         * Floating point exception (core dumped)
         */
        // cout << (1 / 0) << endl; // Uncomment to see the undefined behaviour.
        throw "Unknown exception occurred";
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
    /**
     * Importance of catching order of exceptions. `bad_alloc()` class is the subclasss
     * of `exception()` class. Thus, `bad_alloc` exception is catched by 
     * `(exception &e)` instead of `(bad_alloc &e)` Polymorphism. The subclass must be
     * before its parent class. Otherwise, `catch (bad_alloc &e)` becomes useless
     * because `catch (exception &e)` is before it.
     * 
     * The correct should is below:
     * try {
     *     goes_wrong();
     * } catch (bad_alloc &e) {
     *     cout << "Catching exception: " << e.what() << endl;
     * } catch (exception &e) {
     *     cout << "Catching exception: " << e.what() << endl;
     * }
     */
    try {
        goes_wrong();  // Throw `bad_alloc()`.
    } catch (exception &e) {
        cout << "Catching exception: " << e.what() << endl;
    } catch (bad_alloc &e) {  // This catch is useless.
        cout << "Catching bad_alloc: " << e.what() << endl;
    }

    // Customize my own exception.
    Test test;
    try {
        test.goes_wrong();
    } catch (MyException &e) {
        cout << e.what() << endl;
    }

    // Throw an unknown exception while running.
    try {
        test.throw_unknown_exception();
    } catch (exception &e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "Caught an unknown exception." << endl;

        // Log additional information
        cout << "Exception caught. Logging stack trace and program state:" << endl;

        // Log stack trace or other relevant information here...

        // There is NOTHING I can do to insepct what the exception is thrown but rethrow it.
        // throw;  // throw the same error again to be handled somewhere else
    }

    // exception is thrown all the way out to main() through call stacks.
    try {
        uses_might_go_wrong();
    } catch (int e) {
        cout << "Error code:" << e << endl;
    } catch (char const *e) {
        cout << "string literal error message: " << e << endl;
    } catch (string &e) { // Use e or &e?
        cout << "std::string error message: " << e << endl;
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
