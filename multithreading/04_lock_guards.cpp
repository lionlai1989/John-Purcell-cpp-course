#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void work(int &count, mutex &mtx) {
    for (int i = 0; i < 1e6; i++) {
        /**
         * RAII: Resource Acquisition is Initialization
         * The idea of lock_guard is that if we want to acquire some resource, for example in this
         * case, we want to acquire a lock, we do it by initializing some variables. And then if
         * that variable should go out of scope for any reason, even if an exception is thrown, then
         * it will release the resource or it can be made to do that. So here we're going to use
         * lock_gurad instead of mutex.
         * 
         * lock_guard is the same as calling lock on a mutex. BUT when it goes out of scope, this is
         * the different thing, it will release the lock automatically. E.g., it is going to go out
         * of scope when it hits the curly bracket of the for loop here. So every time we go around
         * the loop, we're going to be acquiring the lock and then releasing the lock. The critical
         * section exists between "lock_guard<mutex> guard(mtx);" and wherever the next sort of
         * closing bracket is.
         */
        lock_guard<mutex> guard(mtx); // Start of the critical section.
        // unique_lock<mutex> guard(mtx); unique_lock has the explicit unlock function.

        ++count;
    } // End of the critical section.
}

// Example command: g++ -Wall -std=c++17 -pthread 04_lock_guards.cpp && ./a.out
int main() {
    int count = 0;
    mutex mtx;

    thread t1(work, ref(count), ref(mtx));
    thread t2(work, ref(count), ref(mtx));

    t1.join();
    t2.join();
    cout << count << endl; // 2000000

    return 0;
}
