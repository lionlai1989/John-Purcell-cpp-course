#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

// g++ -Wall -std=c++17 -pthread 12_checking_condition_shared_resources.cpp && ./a.out
int main() {
    std::condition_variable condition;
    std::mutex mtx;
    bool ready1 = false;

    std::thread t1([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        std::cout << "t1 acquiring lock" << std::endl;
        std::unique_lock<std::mutex> lock1(mtx);
        std::cout << "t1 acquired lock" << std::endl;

        ready1 = true;
        std::cout << "t1 released lock; notifying" << std::endl;
        lock1.unlock();

        // It must notify here so the main thread can be notified. In other words, if
        // `notify_one` is not called, the main thread will hang at `wait` forever even
        // `ready1` already turns to `true`. This is necessary because if `notify_one`
        // is not introduced in the design, the CPUs have to continuously check
        // `ready1`'s state which is a waste of CPU power.
        condition.notify_one();
    });

    std::cout << "main thread acquiring lock" << std::endl;
    std::unique_lock<std::mutex> lock2(mtx);

    std::cout << "main thread acquired lock; waiting" << std::endl;
    /**
     * While the main thread is waiting at this point, it atomically releases the mutex
     * and suspends thread execution until the condition variable is notified. Thus, in
     * order to making the program continue to run, the following things must happen:
     *
     * - `ready1` is assigned to `true`.
     * - `condition` is notified.
     */
    condition.wait(lock2, [&]() { return ready1; });

    std::cout << "main thread finished waiting" << std::endl;
    std::cout << "ready1: " << ready1 << std::endl; // ready1: 1

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
