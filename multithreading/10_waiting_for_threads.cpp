#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

// g++ -Wall -std=c++17 -pthread 10_waiting_for_threads.cpp && ./a.out
int main() {
    /**
     * In this tutorial, we're going to look at a situation where one thread has to wait for another
     * thread before it can proceed, and this is going to motivate an examination of conditions
     * variables.
     */
    bool ready1 = false;

    /**
     * thread_local means that each thread will definitely get its own copy of the variable.
     */
    thread_local bool ready2 = false;

    /**
     * atomic guarantees that the variable is used across different threads, whatever systems or
     * compilers are used.
     */
    std::atomic<bool> ready3 = false;

    std::thread t1([&]() {
        // In this thread, it does something to make main() wait.
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        ready1 = true;
    });
    std::thread t2([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        ready2 = true;
    });
    std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        ready3 = true;
    });

    /**
     * We can use a while loop to wait for ready becoming true.
     */
    while (!ready1) {
        // Check the "ready" variable every 100 milliseconds.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Wait for ready1 ..." << std::endl; // Print many "Wait for ready1 ...".
    }
    std::cout << "ready1: " << ready1 << std::endl; // ready1: 1

    while (!ready3) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Wait for ready3 ..." << std::endl; // No "Wait for ready3 ..." is printed.
    }
    std::cout << "ready3: " << ready3 << std::endl; // ready3: 1

    while (!ready2) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Wait for ready2 ..." << std::endl; // Print "Wait for ready2 ..." eternally.
    }
    std::cout << "ready2: " << ready2 << std::endl;
    // The program hangs eternally here, because the ready2 in main() is different from the ready2
    // in the thread t2. Thus, the ready2 in main() is never set to true.

    t1.join(); // The function returns when the thread execution has completed.
    t2.join();
    t3.join();
    return 0;
}
