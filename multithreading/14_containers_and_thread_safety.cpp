#include <iostream>
#include <queue>
#include <thread>

template <typename T>
class BlockingQueue {
  private:
    int _max_size;
    std::queue<T> _queue;

  public:
    BlockingQueue(int max_size) : _max_size(max_size) {}

    void push(T t) {
        _queue.push(t);
        // cout << "Push" << endl;
    }

    T pop() {
        T item = _queue.front(); // accessing an element.
        _queue.pop();            // popping off an element.
        // cout << "Pop" << endl;
        return item;
    }
};

// g++ -Wall -std=c++17 -pthread 14_containers_and_thread_safety.cpp && ./a.out
int main() {
    /**
     * Thread safety:
     * We usually mean a function could be thread safe, we usually mean that this function can be
     * used by multiple threads and you don't have to worry about synchronization. So the question
     * here is that if the STL queue itself is thread safe for all the containers in the standard
     * template library. The answer is it depends. Check out the "Thread Safety" section in
     * https://en.cppreference.com/w/cpp/container and google this topic in stackoverflow. Thus, the
     * best thing we can do in general is putting some synchronization ourselves when we are
     * accessing containers from multiple threads. By doing this, we will know what is happening
     * under the hood and do not have to worry about this issue. That's what we are doing here. We
     * are trying to build a blocking queue based on the STL queue.
     */
    BlockingQueue<int> qu(5);

    std::thread t1([&]() {
        // Producer
        for (int i = 0; i < 10; i++) {
            qu.push(i);
            std::cout << "Produced " << i << std::endl;
        }
    });

    std::thread t2([&]() {
        // Consumer
        for (int i = 0; i < 10; i++) {
            auto item = qu.pop();
            std::cout << "Consumed " << item << std::endl;
        }
    });

    t1.join();
    t2.join();
    /**
     * The output shows that it seems fine (the program will not crash) when popping elements faster
     * from queue than pushing elements into queue. It just returns 0. And it is not what we want,
     * because we also want the consumer to consume the elements correctly.
     * Output:
     * Produced Consumed 00
     * Produced 1
     * Produced 2
     * Produced
     * Consumed 1
     * Consumed 2
     * Consumed 3
     * Consumed 0
     * Consumed 0
     * Consumed 0
     * Consumed 0
     * Consumed 0
     * Consumed 0
     * 3
     * Produced 4
     * Produced 5
     * Produced 6
     * Produced 7
     * Produced 8
     * Produced 9
     */

    return 0;
}
