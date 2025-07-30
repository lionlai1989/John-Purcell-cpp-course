#include <iostream>
#include <thread>

template <typename T> class BlockingQueue {
  public:
    void push(T t) { std::cout << "Push" << std::endl; }

    void pop() { std::cout << "Pop" << std::endl; }
};

// g++ -Wall -std=c++17 -pthread 13_using_methods_in_threads.cpp && ./a.out
int main() {
    BlockingQueue<int> qu;
    std::thread t1(&BlockingQueue<int>::push, &qu, 7);
    std::thread t2(&BlockingQueue<int>::pop, &qu);

    t1.join();
    t2.join();
    /**
     * Output:
     * PushPop
     *
     */

    return 0;
}
