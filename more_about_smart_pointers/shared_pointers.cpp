#include <iostream>
#include <memory> // Smart pointers.

using namespace std;

class Test {
  public:
    Test() {
        cout << "Created" << endl;
    }

    void greet() {
        cout << "Hello" << endl;
    }

    ~Test() {
        cout << "Destroyed" << endl;
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 shared_pointers.cpp && ./a.out
int main() {
    /**
     * shared_ptr:
     * std::shared_ptr is a smart pointer that retains shared ownership of an object through a
     * pointer. Several shared_ptr objects may own the same object. The object is destroyed and its
     * memory deallocated when either of the following happens: 
     * - the last remaining shared_ptr owning the object is destroyed;
     * - the last remaining shared_ptr owning the object is assigned another pointer via operator=
     *   or reset().
     * 
     * Following on from the tutorial on unique pointers, shared pointers are really similar. shared
     * pointers just add a little twist which is that they don't delete the memory associated with
     * your objects until all the pointers that point at that object have gone out of scope. 
     * 
     * At the moment, shared_ptr cannot point to arrays, but that might change in C++17, but here in
     * 2015 we can only use shared pointers to point to an individual object.
     */
    {
        shared_ptr<Test> p_test1(new Test());
        p_test1->greet();
        /**
         * p_test1 is out of scope when it reaches the end of the closing curly brackets.
         * 
         * Output:
         * Created
         * Hello
         * Destroyed
         */
    }

    /**
     * Now, according to the documentation, the kind of the best way to create a shared pointer is
     * to use make_shared template function. It is more efficient than using "p_test1(new Test())".
     * 
     * make_shared:
     * Allocates and constructs an object of type T passing args to its constructor, and returns an
     * object of type shared_ptr<T> that owns and stores a pointer to it (with a use count of 1). 
     */
    shared_ptr<Test> p_test3 = nullptr;
    {
        shared_ptr<Test> p_test2 = make_shared<Test>();
        p_test3 = p_test2;
    }
    /**
     * What is happening here is that when p_test2 is out of scope, the Test object still exists
     * because p_test3 which also points to the same Test object have not gone out of scope. That is
     * why the Test object is being destroyed at the end of the program.
     *
     * Output:
     * Created
     * Finished
     * Destroyed
     */

    cout << "Finished" << endl;

    return 0;
}
