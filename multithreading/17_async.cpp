#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int work(int id) {
    for (int i = 0; i < 5; i++) {
        std::cout << "Running " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 7 * id;
}

// g++ -Wall -std=c++17 -pthread 17_async.cpp && ./a.out
int main() {
    /**
     * std::async
     * -----------
     * The function template async runs the function f either:
     *   • in a new thread of execution (if std::launch::async is used), or
     *   • deferred until we call get()/wait() on the returned future (if std::launch::deferred).
     *
     * It returns a std::future<R> that will eventually hold the result of f().
     *
     * Note on destructors:
     * If we create a std::future via std::async and then immediately let that future be destroyed
     * (e.g. as a temporary), its destructor will block until the associated task has completed.
     *   - For async-launched tasks, it waits for the thread to finish.
     *   - For deferred tasks, it runs the task synchronously on destruction.
     *
     * Always store std::future (or explicitly call .get()/.wait()) to control when and how the
     * asynchronous or deferred task executes.
     */

    // Example 1: deferred launch
    // std::launch::deferred means "don’t run `work(0)` now; run it only when f0.get() is called."
    std::future<int> f0 = std::async(std::launch::deferred, work, 0);
    std::cout << "f0: " << f0.get() << std::endl;
    // work(0) executes here, printing "Running 0" five times, then returns 0

    // Example 2: async launch
    // std::launch::async means "spawn a new thread now to run work(arg)"
    std::future<int> f1 = std::async(std::launch::async, work, 1);
    std::future<int> f2 = std::async(std::launch::async, work, 2);
    std::cout << "f1: " << f1.get() << std::endl; // waits for work(1), returns 7
    std::cout << "f2: " << f2.get() << std::endl; // waits for work(2), returns 14

    /**
     * We can observe that f0 is running first. After f0 is finished running and returns value 0, f1
     * and f2 start running. f1 and f2 run asynchronously.
     * Output:
     * f0: Running 0
     * Running 0
     * Running 0
     * Running 0
     * Running 0
     * 0
     * Running 1
     * f1: Running 2
     * Running 1
     * Running 2
     * Running 1
     * Running 2
     * Running 1
     * Running 2
     * Running 1
     * Running 2
     * 7
     * f2: 14
     */

    return 0;
}
