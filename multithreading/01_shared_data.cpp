#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

// Example command: g++ -Wall -std=c++17 -pthread 01_shared_data.cpp && ./a.out
int main() {
    int count1 = 0, count2 = 0;
    const int ITERATIONS = 100000;

    // "thread t([](){});": Each of these different brackets serves a purpose in the lambda
    // expression.
    // "()": The round brackets is for passing parameters.
    // "{}": The curly brackets is where your code goes.
    // "[]": The square brackets is what we use to store the variables from its environment the
    // lambda expression can use.
    thread t1([&count1]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count1;
        }
    });

    t1.join();
    cout << count1 << endl; // 100000

    thread t2([&count2]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count2;
        }
    });
    thread t3([&count2]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count2;
        }
    });
    t2.join();
    t3.join();
    cout << count2 << endl; // The output is not necessarily 200000. Usually it's smaller than 200000.

    atomic<int> count3 = 0;
    // Using atomic should be able to tackle the issue in this simple example. But it is not going
    // to work generally in a general case where we want multiple threads to operate on the same
    // data.
    thread t4([&count3]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count3;
        }
    });
    thread t5([&count3]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count3;
        }
    });
    t4.join();
    t5.join();
    cout << count3 << endl; // The output should always be 200000.

    return 0;
}
