#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class BlockingQueue {
  private:
    std::mutex _mtx;
    std::condition_variable _cond;
    unsigned int _max_size;
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

std::mutex g_mtx;
int work(int id) {
    std::unique_lock<std::mutex> lock(g_mtx);
    std::cout << "Starting " << id << std::endl;
    lock.unlock();

    /**
     * Each thread consumes random number of seconds.
     */
    int seconds = int((5.0 * rand()) / RAND_MAX + 3);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    return id;
}

// g++ -Wall -std=c++17 -pthread 20_a_thread_pool.cpp && ./a.out
int main() {
    /**
     * Now we're going to supply a number to the constructor of BlockingQueue, and this is going to
     * be one less than the total number of threads that we want to create, one less, because as we
     * see, that's just kind of an artifact of how we've implemented this.
     *
     * Now, what should the number of threads that we create actually be? Well, if your function
     * that's doing your work is a CPU intensive function and you want to distribute the work
     * efficiently over however many threads you can actually run at the same time, literally run at
     * the same time on different cores, then you probably want to set this number to, well, it
     * would be one less than hardware_concurrency(). E.g., if you've got four cores, you want to
     * run four threads at the same time for maximum efficiency to get through the work as fast as
     * possible. On the other hand, if you're waiting for some external resource and you just want
     * asynchronous functions here, then you might choose a number that's much bigger than four.
     *
     * But for demonstration purposes here, let's use 2. In other words, we're going to run
     * maximum of three threads at any given time. When the third thread is started,
     * "shared_future<int> f = async(launch::async, work, i);", the return value, f, cannot be push
     * back to queue (becuase it already has 2 elements in it) until the element is pop out of the
     * queue.
     *
     */

    // We run 2+1=3 threads at a time. 2 threads in queue already. 1 thread already started but the
    // queue is full so it's waiting to be pushed into queue.
    BlockingQueue<std::shared_future<int>> futures(2);

    std::thread t([&]() {
        /**
         * The number of futures that this thread here can actually push onto the queue is
         * constrained by the size of the queue.
         */
        for (int i = 0; i < 10; i++) {
            std::shared_future<int> f = std::async(std::launch::async, work, i);
            futures.push(f);
        }
    });

    for (int i = 0; i < 10; i++) {
        std::shared_future<int> f = futures.front();
        int value = f.get();
        // After each thread finishes, we're going to pop off the front of the queue.
        futures.pop();
        std::cout << "Returned: " << value << std::endl;
    }

    t.join();
    /**
     * Output:
     * Starting 0
     * Starting 2
     * Starting 1 // The program run maximum three threads at a time.
     * Returned: 0 // Pop an element out of the queue.
     * Returned: 1
     * Starting Returned: 2
     * 3
     * Starting 5
     * Starting 4
     * Returned: 3
     * Returned: 4
     * Starting 6
     * Starting 7
     * Returned: 5
     * Starting 8
     * Returned: 6
     * Starting 9
     * Returned: 7
     * Returned: 8
     * Returned: 9
     *
     * We've got three threads running at any given time.
     */

    return 0;
}
