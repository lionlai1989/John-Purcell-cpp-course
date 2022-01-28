#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void work(int &count, mutex &mtx) {
    for (int i = 0; i < 1e6; i++) {
        mtx.lock();
        ++count;
        mtx.unlock();
    }
}

// Example command: g++ -Wall -std=c++17 -pthread 03_function_arguments.cpp && ./a.out
int main() {
    int count = 0;
    mutex mtx;

    // std::thread passes parameters with call by value, but we want to pass a reference here. Thus
    // ref() is essential here.
    thread t1(work, ref(count), ref(mtx));
    thread t2(work, ref(count), ref(mtx));

    t1.join();
    t2.join();
    cout << count << endl; // 2000000

    return 0;
}
