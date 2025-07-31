#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class BlockingQueue {
  private:
    std::mutex _mtx;
    std::condition_variable _cond;
    int _max_size;
    std::queue<T> _queue;

  public:
    BlockingQueue(int max_size) : _max_size(max_size) {}

    void push(T t) {
        std::unique_lock<std::mutex> lock(_mtx);

        _cond.wait(lock, [this]() { return _queue.size() < _max_size; });

        _queue.push(t);

        lock.unlock();

        _cond.notify_one();
    }

    T front() {
        std::unique_lock<std::mutex> lock(_mtx);

        _cond.wait(lock, [this]() { return !_queue.empty(); });

        return _queue.front();
    }

    void pop() {
        std::unique_lock<std::mutex> lock(_mtx);

        _cond.wait(lock, [this]() { return !_queue.empty(); });

        _queue.pop();

        lock.unlock();

        _cond.notify_one();
    }

    int size() {
        std::lock_guard<std::mutex> lock(_mtx);
        return _queue.size();
    }
};

// g++ -Wall -std=c++17 -pthread 16_a_blocking_queue.cpp && ./a.out
int main() {
    /**
     * In this tutorial, we are going to make a couple of adjustments to the code we've got in
     * 15_producer_consumer.cpp to finish off our blocking queue.
     *
     * Now, one thing we have to pay attention to is the size() method in BlockingQueue, because it
     * returns the size of queue with no synchronization. Thus, we add the front() method and modify
     * the size() and pop() methods.
     */
    BlockingQueue<int> qu(5);

    std::thread t1([&]() {
        // Producer
        for (int i = 0; i < 10; i++) {
            std::cout << "Pushing " << i << std::endl;
            qu.push(i);
            std::cout << "queue size is " << qu.size() << std::endl;
        }
    });

    std::thread t2([&]() {
        // Consumer
        for (int i = 0; i < 10; i++) {
            auto item = qu.front();
            qu.pop();
            std::cout << "Consumed " << item << std::endl;
        }
    });

    t1.join();
    t2.join();

    /**
     * As we can see, our blocking queue also works and are better than 15_producer_consumer.cpp.
     *
     * Output:
     * Pushing 0
     * queue size is 1
     * Pushing 1
     * queue size is 2
     * Pushing 2
     * queue size is 3
     * Pushing 3
     * queue size is 4
     * Pushing 4
     * queue size is 5
     * Pushing 5
     * Consumed 0
     * Consumed 1
     * Consumed 2
     * Consumed 3
     * Consumed 4
     * Consumed 5
     * queue size is 0
     * Pushing 6
     * queue size is 1
     * Pushing 7
     * queue size is 2
     * Pushing 8
     * queue size is 3
     * Pushing 9
     * queue size is 4
     * Consumed 6
     * Consumed 7
     * Consumed 8
     * Consumed 9
     */

    return 0;
}
