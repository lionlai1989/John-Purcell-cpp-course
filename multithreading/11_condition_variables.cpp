#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

using namespace std;

// Example command: g++ -Wall -std=c++17 -pthread 11_condition_variables.cpp && ./a.out
int main() {
    condition_variable condition;
    mutex mtx;
    bool ready1 = false;

    thread t1([&]() {
        this_thread::sleep_for(chrono::milliseconds(2000));

        /**
         * The reason that unique_lock is used instead of lock_guard is that we need the unlock method.
         */
        unique_lock<mutex> lock1(mtx);

        ready1 = true;
        lock1.unlock();

        /**
         *  The idea is that we have a thread that are waiting for something to happen in the
         *  present thread and we can notify this thread to wake up and try to do whatever it is
         *  waiting to be able to do. 
         */
        condition.notify_one();
    });

    /**
     * The unique_lock lock2 here needs to get the lock associated with the same mutex as lock1's.
     * Namely, the constructors of these unique_lock objects, lock1 and lock2, needs to supply with
     * the same mutex that we are going to lock on. 
     */
    unique_lock<mutex> lock2(mtx);

    while (!ready1) {
        condition.wait(lock2);
        cout << "Wait for ready1 ..." << endl;
        // Print "Wait for ready1 ..." only once, because "condition.wait(lock2);" waits for
        // notify_one().
    }
    cout << "ready1: " << ready1 << endl; // ready1: 1

    t1.join(); // The function returns when the thread execution has completed.

    return 0;
}
