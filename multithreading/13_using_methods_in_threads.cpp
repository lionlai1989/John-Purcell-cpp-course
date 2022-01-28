#include <iostream>
#include <thread>

using namespace std;

template <typename T>
class BlockingQueue {
  public:
    void push(T t) {
        cout << "Push" << endl;
    }

    void pop() {
        cout << "Pop" << endl;
    }
};

// Example command: g++ -Wall -std=c++17 -pthread 13_using_methods_in_threads.cpp && ./a.out
int main() {
    BlockingQueue<int> qu;
    thread t1(&BlockingQueue<int>::push, &qu, 7);
    thread t2(&BlockingQueue<int>::pop, &qu);

    t1.join();
    t2.join();
    /**
     * Output:
     * PushPop
     * 
     */

    return 0;
}
