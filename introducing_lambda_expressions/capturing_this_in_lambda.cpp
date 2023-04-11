#include <iostream>

using namespace std;

class Test {
  private:
    // Instance variables.
    int one = 1;
    int two = 2;

  public:
    void run() {
        int three = 3;
        int four = 4;

        /**
         * "one" and "two" can not be captured because they are private/instance variables.
         * auto pLambda = [one, two]() {};
         */
        auto pLambda = [three, four]() {
            cout << three << endl; // 3
            cout << four << endl;  // 4
        };
        pLambda();

        /**
         * "this" is captured by reference. "three" and "four" are captured by value. Thus, "three"
         * and "four" cannot be modified.
         * Note: 
         * auto another_pLambda = [=, this]() --> throw compiling error. "=" means captured by
         * value but "this" means captured by reference.
         * 
         * auto another_pLambda = [&, this]() --> will work.
         */
        auto another_pLambda = [this, three, four]() {
            cout << one << endl; // 1
            one = 111;
            cout << one << endl;   // 111
            cout << two << endl;   // 2
            cout << three << endl; // 3
            cout << four << endl;  // 4
        };
        another_pLambda();
    }
};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 capturing_this_in_lambda.cpp && ./a.out
int main() {
    Test test;
    test.run();

    return 0;
}
