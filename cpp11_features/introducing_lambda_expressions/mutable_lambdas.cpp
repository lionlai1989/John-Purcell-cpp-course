#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// Example command: g++ -Wall -std=c++11 -std=gnu++11 mutable_lambdas.cpp && ./a.out
int main() {
    int cats = 5;

    /**
     * By default, cats is captured by value. So, I cannot change the value of cats within the
     * lambda expression. But if we really want to change the value of cats, we can put the keyword
     * mutable into the lambda expression after the round brackets "()". 
     * NOTE: cats is still captured by value. We don't want to use capture by reference here.
     * Because capture by reference will change the value of cats outside of lambda expressions.
     */
    [cats]() mutable {
        cout << cats << endl; // 5
        cats = 8;
        cout << cats << endl; // 8
    }();

    // However, the local variable cats is not being changed.
    cout << cats << endl; // 5
    return 0;
}
