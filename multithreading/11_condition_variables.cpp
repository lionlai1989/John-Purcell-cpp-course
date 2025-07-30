#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

// g++ -Wall -std=c++17 -pthread 11_condition_variables.cpp && ./a.out
int main() {
    std::condition_variable condition;
    std::mutex mtx;
    bool ready1 = false;

    std::thread t1([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        /**
         * The reason that unique_lock is used instead of lock_guard is that we need the unlock
         * method.
         */
        std::unique_lock<std::mutex> lock1(mtx);

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
    std::unique_lock<std::mutex> lock2(mtx);

    while (!ready1) {
        std::cout << "Wait for ready1 ..." << std::endl;
        // Print "Wait for ready1 ..." only once, because "condition.wait(lock2);" waits for
        // notify_one().

        condition.wait(lock2);

        std::cout << "lock2 is unlocked ..." << std::endl;
    }
    std::cout << "ready1: " << ready1 << std::endl; // ready1: 1

    t1.join(); // The function returns when the thread execution has completed.

    return 0;
}
