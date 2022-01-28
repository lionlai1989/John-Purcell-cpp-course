#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex g_mtx;

int work1(int id) {
    cout << "Starting " << id << endl;
    this_thread::sleep_for(chrono::seconds(3));
    return id;
}

int work2(int id) {
    /**
     * We want to make sure that all the code in work2() can only be run by one thread at a time so
     * that the output doesn't get confused and disorder.
     */
    unique_lock<mutex> lock(g_mtx);
    cout << "Starting " << id << endl;
    lock.unlock();

    this_thread::sleep_for(chrono::seconds(3));
    return id;
}

// Example command: g++ -Wall -std=c++17 -pthread 19_launching_lots_of_threads.cpp && ./a.out
int main() {
    /**
     * If we simply want a asynchronous behavior, eg, we're waiting for some external resource, we
     * could use some big number potentially for the number of threads. But if we really have some
     * heavy work that needs to be distributed over multiple calls and run in parallel, there's no
     * point firing more threads than thread::hardware_concurrency(). Thus, we use
     * hardware_concurrency()=4 here. 
     */
    for (int i = 0; i < thread::hardware_concurrency(); i++) {
        future<int> f = async(launch::async, work1, i);
    }
    /**
     *Output : 
     * Starting 0 
     * Starting 1 
     * Starting 2 
     * Starting 3
     * 
     * We can observe it runs synchorously instead of asynchorously. The problem is that the
     * future here is just going out of scope and that's causing these threads to run synchronously.
     * Essentially, we want to keep references to these return futures. So let's put them in a
     * vector.
     */

    // Here, future cannot be used like above, because future is not copyable. Thus, we must use
    // shared_future.
    // vector<shared_future<int>> futures;
    // for (int i = 0; i < thread::hardware_concurrency(); i++) {
    //     shared_future<int> f = async(launch::async, work1, i);
    //     futures.push_back(f);
    // }
    /**
     * Output:
     * Starting Starting 20
     * 
     * Starting 3
     * Starting 1
     * 
     * We can keep the references by putting them into a vector. Now, the output here is horribly
     * disordered because writing a line of text is not any kind of atomic operation, but we could
     * actually fix that and make this look a bit nicer using a mutex. 
     */

    // work2() uses lock
    vector<shared_future<int>> futures;
    for (int i = 0; i < thread::hardware_concurrency(); i++) {
        shared_future<int> f = async(launch::async, work2, i);
        futures.push_back(f);
    }
    /**
     * Output:
     * Starting 1
     * Starting 3
     * Starting 0
     * Starting 2
     * 
     * These 4 threads run asynchronously as we want to.
     */

    // Get the output
    for (auto f : futures) {
        cout << "Returned: " << f.get() << endl;
    }
    /**
     * Output:
     * Starting 0
     * Starting 1
     * Returned: Starting 3
     * Starting 2
     * 0
     * Returned: 1
     * Returned: 2
     * Returned: 3
     * 
     * As you can see, the order of "Starting" is, you know, it's kind of all over the place. That
     * is just going to depend on how long it takes to start up. The fact that we're doing them in a
     * loop, doesn't mean that they all start up in a tidy order. zero, one, two, three. You know,
     * so therefore, this is going to come out in unpredictable order, depending on exactly when
     * each one gets started. 
     * And we can see that we've got all our return values, "Returned". Finally, zero, one, two,
     * three. And they are in order because we push the futures to the vector in order,
     * "futures.push_back(f);".
     */

    return 0;
}
