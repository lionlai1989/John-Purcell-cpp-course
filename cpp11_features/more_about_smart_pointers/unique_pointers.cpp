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
    unique_ptr<Test[]> p_test;

  public:
    Temp() : p_test(new Test[2]) {
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 unique_pointers.cpp && ./a.out
int main() {
    unique_ptr<int> p_test1(new int);
    *p_test1 = 7;
    cout << *p_test1 << endl;

    unique_ptr<Test> p_test2(new Test);
    p_test2->greet();

    {
        unique_ptr<Test> p_test3(new Test);
        p_test3->greet();
    }

    /**
     * Do not use auto_ptr which is deprecated.
     * auto_ptr<Test> p_test4(new Test);
     * p_test4->greet();
     */

    unique_ptr<Test[]> p_test5(new Test[3]);
    p_test5[1].greet();

    Temp temp;

    cout << "Finished" << endl;

    return 0;
}
