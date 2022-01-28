#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

// Example command: g++ -Wall -std=c++17 -pthread 10_waiting_for_threads.cpp && ./a.out
int main() {
    /**
     * In this tutorial, we're going to look at a situation where one thread has to wait for another
     * thread before it can proceed, and this is going to motivate an examination of conditions
     * variables.
     */
    bool ready1 = false;

    /**
     * thread_local means that each thread will definitely get its own copy of the variable.
     * 
     * atomic guarantees that the variable is used across different threads, whatever systems or
     * compilers are used.
     */
    thread_local bool ready2 = false;
    atomic<bool> ready3 = false;

    thread t1([&]() {
        // In this thread, it does something to make main() wait.
        this_thread::sleep_for(chrono::milliseconds(3000));
        ready1 = true;
    });
    thread t2([&]() {
        this_thread::sleep_for(chrono::milliseconds(3000));
        ready2 = true;
    });
    thread t3([&]() {
        this_thread::sleep_for(chrono::milliseconds(3000));
        ready3 = true;
    });

    /**
     * We can use a while loop to wait for ready becoming true.
     */
    while (!ready1) {
        // Check the "ready" variable every 100 milliseconds.
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Wait for ready1 ..." << endl; // Print many "Wait for ready1 ...".
    }
    cout << "ready1: " << ready1 << endl; // ready1: 1

    while (!ready3) {
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Wait for ready3 ..." << endl; // No "Wait for ready3 ..." is printed.
    }
    cout << "ready3: " << ready3 << endl; // ready3: 1

    while (!ready2) {
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Wait for ready2 ..." << endl; // Print "Wait for ready2 ..." eternally.
    }
    cout << "ready2: " << ready2 << endl;
    // The program hangs eternally here, because the ready2 in main() is different from the ready2
    // in the thread t2. Thus, the ready2 in main() is never set to true.

    t1.join(); // The function returns when the thread execution has completed.
    t2.join();
    t3.join();
    return 0;
}
