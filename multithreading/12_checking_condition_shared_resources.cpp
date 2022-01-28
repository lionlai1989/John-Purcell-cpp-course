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

        condition.notify_one();
    });

    cout << "main thread acquiring lock" << endl;
    unique_lock<mutex> lock2(mtx);

    cout << "main thread acquired lock; waiting" << endl;
    condition.wait(lock2, [&]() { return ready1; });

    cout << "main thread finished waiting" << endl;
    cout << "ready1: " << ready1 << endl; // ready1: 1

    t1.join();

    /**
     * Output:
     * main thread acquiring lock
     * main thread acquired lock; waiting
     * t1 acquiring lock
     * t1 acquired lock
     * t1 released lock; notifying
     * main thread finished waiting
     * ready1: 1
     */

    return 0;
}
