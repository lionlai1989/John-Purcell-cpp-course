#include <iostream>
#include <mutex>
#include <thread>

void work(int &count, std::mutex &mtx) {
    for (int i = 0; i < 1e6; i++) {
        mtx.lock();
        ++count;
        mtx.unlock();
    }
}

// g++ -Wall -std=c++17 -pthread 03_function_arguments.cpp && ./a.out
int main() {
    int count = 0;
    std::mutex mtx;

    // std::thread passes parameters with call by value, but we want to pass a reference here. Thus
    // ref() is essential here.
    std::thread t1(work, std::ref(count), std::ref(mtx));
    std::thread t2(work, std::ref(count), std::ref(mtx));

    t1.join();
    t2.join();
    std::cout << count << std::endl; // 2000000

    return 0;
}
