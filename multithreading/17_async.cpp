#include <chrono>
#include <future>
#include <iostream>

using namespace std;

int work(int id) {
    for (int i = 0; i < 5; i++) {
        cout << "Running " << id << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return 7 * id;
}

// Example command: g++ -Wall -std=c++17 -pthread 17_async.cpp && ./a.out
int main() {
    /**
     * std::async
     * The function template async runs the function f asynchronously (potentially in a separate
     * thread which might be a part of a thread pool) and returns a std::future that will eventually
     * hold the result of that function call.
     * If the std::future obtained from std::async is not moved from or bound to a reference, the
     * destructor of the std::future will block at the end of the full expression until the
     * asynchronous operation completes, essentially making code such as the following synchronous:
     * std::async(std::launch::async, []{ f(); }); // temporary's dtor waits for f()
     * std::async(std::launch::async, []{ g(); }); // does not start until f() completes
     * 
     * async can run things in two modes, deferred and async. If we choose deferred, then the thread
     * is not going to launch until we could get from the future.
     */

    future<int> f0 = async(launch::deferred, work, 0);
    cout << "f0: " << f0.get() << endl;

    future<int> f1 = async(launch::async, work, 1);
    future<int> f2 = async(launch::async, work, 2);
    cout << "f1: " << f1.get() << endl;
    cout << "f2: " << f2.get() << endl;
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
