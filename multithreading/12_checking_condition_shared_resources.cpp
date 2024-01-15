#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

using namespace std;

// Example command: g++ -Wall -std=c++17 -pthread 12_checking_condition_shared_resources.cpp && ./a.out
int main() {
    condition_variable condition;
    mutex mtx;
    bool ready1 = false;

    thread t1([&]() {
        this_thread::sleep_for(chrono::milliseconds(3000));

        cout << "t1 acquiring lock" << endl;
        unique_lock<mutex> lock1(mtx);
        cout << "t1 acquired lock" << endl;

        ready1 = true;
        cout << "t1 released lock; notifying" << endl;
        lock1.unlock();

        // It must notify here so the main thread can be notified. In other words, if
        // `notify_one` is not called, the main thread will hang at `wait` forever even
        // `ready1` already turns to `true`. This is necessary because if `notify_one`
        // is not introduced in the design, the CPUs have to continuously check
        // `ready1`'s state which is a waste of CPU power.
        condition.notify_one();
    });

    cout << "main thread acquiring lock" << endl;
    unique_lock<mutex> lock2(mtx);

    cout << "main thread acquired lock; waiting" << endl;
    /**
     * While the main thread is waiting at this point, it atomically releases the mutex
     * and suspends thread execution until the condition variable is notified. Thus, in
     * order to making the program continue to run, the following things must happen:
     * 
     * - `ready1` is assigned to `true`.
     * - `condition` is notified.
    */
    condition.wait(lock2, [&]() { return ready1; });

    cout << "main thread finished waiting" << endl;
    cout << "ready1: " << ready1 << endl; // ready1: 1

    t1.join();

    /**
     * Output:
     * main thread acquiring lock
     * main thread acquired lock; waiting
     * (waiting for 3000 milliseconds)
     * t1 acquiring lock
     * t1 acquired lock
     * t1 released lock; notifying
     * main thread finished waiting
     * ready1: 1
     */

    return 0;
}
