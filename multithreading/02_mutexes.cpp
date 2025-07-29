#include <iostream>
#include <mutex>
#include <thread>

// g++ -Wall -std=c++17 -pthread 02_mutexes.cpp && ./a.out
int main() {
    int count = 0;
    const int ITERATIONS = 1e6;

    std::mutex mtx;

    auto func = [&]() {
        for (int i = 0; i < ITERATIONS; i++) {
            // "++count;": the critical section.
            // From a theoretical perspective, a critical section is a piece of code that must not
            // be run by multiple threads at once because the code accesses shared resources. A
            // mutex is an algorithm (and sometimes the name of a data structure) that is used to
            // protect critical sections. Here, "mtx.lock();" locks the critical section and
            // "mtx.unlock();" unlocks the critical section. If the unlock is not called, the whole
            // program will just hang.
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };

    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    std::cout << count << std::endl; // 2000000

    return 0;
}
