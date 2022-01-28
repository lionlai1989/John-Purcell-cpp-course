#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

template <typename T>
class BlockingQueue {
  private:
    mutex _mtx;
    condition_variable _cond;
    int _max_size;
    queue<T> _queue;

  public:
    BlockingQueue(int max_size) : _max_size(max_size) {
    }

    void push(T t) {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this]() { return _queue.size() < _max_size; });

        _queue.push(t);

        lock.unlock();

        _cond.notify_one(); // If more than one, it is unspecified which of the threads is selected.
    }

    T pop() {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this]() { return !_queue.empty(); });

        T item = _queue.front();
        _queue.pop();

        lock.unlock();

        _cond.notify_one(); // If more than one, it is unspecified which of the threads is selected.

        return item;
    }

    int size() {
        return _queue.size();
    }
};

// Example command: g++ -Wall -std=c++17 -pthread 15_producer_consumer.cpp && ./a.out
int main() {
    /**
     * In 14_containers_and_thread_safety.cpp, we show that the STL queue is not thread safe, and we
     * will continue creating a blocking queue to augment the robustness of STL queue.
     */
    BlockingQueue<int> qu(5);

    thread t1([&]() {
        // Producer
        for (int i = 0; i < 10; i++) {
            cout << "Pushing " << i << endl;
            qu.push(i);
            cout << "queue size is " << qu.size() << endl;
        }
    });

    thread t2([&]() {
        // Consumer
        for (int i = 0; i < 10; i++) {
            auto item = qu.pop();
            cout << "Consumed " << item << endl;
        }
    });

    t1.join();
    t2.join();

    /**
     * As we can see, the queue's size never exceeds 5. And the producer and consumer works pretty
     * well. 
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
	 * queue size is 1
	 * Pushing 8
	 * queue size is 2
	 * Pushing 9
	 * queue size is 3
	 * Consumed 6
	 * Consumed 7
	 * Consumed 8
	 * Consumed 9
     */

    return 0;
}
