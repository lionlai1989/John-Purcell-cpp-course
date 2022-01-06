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

class Temp {
  private:
    /**
     * Here, we are not allowed to allocate memory here as below.
     * unique_ptr<Test[]> p_test(new Test[2]);
     * We have to allocate memory in the public constructor.
     */
    unique_ptr<Test[]> p_test;

  public:
    Temp() : p_test(new Test[2]) {
    }

    /**
     * NOTE: There is no destructor here and the Test object will be destroyed anyway when the
     * object is out of scope.
     */
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 unique_pointers.cpp && ./a.out
int main() {
    /**
     * unique_ptr:
     * std::unique_ptr is a smart pointer that owns and manages another object through a pointer and
     * disposes of that object when the unique_ptr goes out of scope. The object is disposed of,
     * using the associated deleter when either of the following happens:
     * - the managing unique_ptr object is destroyed
     * - the managing unique_ptr object is assigned another pointer via operator= or reset().
     * 
     * unique_ptr is a template type. The bracket needs to hold what type of things is going to
     * point to. And the asterisk "*"" is not needed here, because it knows it is a pointer already.
     * 
     * Now we want p_test1 to manage the memory that it allocates with new itself. We cannot just
     * say p_test1 equals new int, "p_test1 = new int". If we want to do that we have to do the
     * memory allocation within the constructor brackets, "p_test1(new int)" 
     */
    unique_ptr<int> p_test1(new int);
    *p_test1 = 7;
    cout << *p_test1 << endl; // 7

    {
        unique_ptr<Test> p_test2(new Test);
        p_test2->greet();
        /**
         * What happens here is that this local variable, p_test2, goes out of scope when it hits
         * the closing bracket "}" (Line 57), and at that point the destructor is called and the
         * memory that we allocated is automatically cleaned up by the unique_ptr.
         * 
         * Output:
         * Created
         * Hello
         * Destroyed
         */
    }

    unique_ptr<Test> p_test3(new Test);
    p_test3->greet();
    /** 
     * The destructor will not be called at this point.
     * Output:
     * Created
     * Hello
     */

    /**
     * Do not use auto_ptr which is deprecated.
     * auto_ptr<Test> p_test4(new Test);
     */

    /**
     * Now an array, Test[], is put in the unique_ptr's template brackets and 2 Test objects are
     * allocated.
     */
    unique_ptr<Test[]> p_test5(new Test[2]);
    p_test5[1].greet();
    /**
     * Two Test objects are created.
     * Output:
     * Created
     * Created
     * Hello
     */

    Temp temp;
    /**
     * Two Test objects are created in the temp object. No destructor is called at this point.
     * Output:
     * Created
     * Created
     */

    cout << "main() Finished" << endl;
    /**
     * There are five objects being destroyed when the program is reaching the end (out-of-scope).
     * Output:
     * main() Finished
     * Destroyed
     * Destroyed
     * Destroyed
     * Destroyed
     * Destroyed
     */

    return 0;
}
