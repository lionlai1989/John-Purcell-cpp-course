#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

/*
 * When is multithreading useful?
 * 
 * 1. When you're waiting for something external and want to execute code meanwhile.
 * (asynchronous execution)
 * 
 * Example: pinging remote servers
 * Example: drawing graphics while also waiting for user inputs with one thread
 * 
 * 2. Distributing process across multiple cores
 * 
 * Example: calculating pi to lots of digits.
 *
 * AN IMPORTANT NOTE:
 * My pc has 4 CPUs. There are 4 cores. So that's effectively 4 processors that can run things at
 * the same time, more or less. Now, each of those cores actually uses something called
 * hyperthreading, meaning each core can actually run two threads at any given time, which means
 * that in theory I can run 8 separate threads at the same time on my computer. So if I had some
 * really heavy work that I wanted to do, in theory, the optimum number of threads to get through
 * that work as fast as possible would be 8, because that's how many my computer can genuinely run
 * simultaneously at the same time. 
 *
 * Now, it's important to realize that often you'll use the first type of multithreading, so let's
 * imagine, for example, that your machine only had one CPU, and that processor can only one run one
 * thread at a time, and you can still run multithreaded code within it and it will work via time
 * slicing. So let's say you're running two threads at the same time. Then your computer will
 * allocate a really brief slice of time to one thread, then a brief slice of time to the next, then
 * a brief slice of time to the first thread and so on. So you'll get an appearance of
 * multithreading, but in reality it can only run one kind of basic thread at a time. 
 *
 * On the other hand, if your aim is to get through a load of really heavy CPU intensive work, it
 * won't do you any good to have multiple threads because they've all got to be executed on the same
 * core anyway. Whereas in the first type situation, multithreading is still useful because although
 * you'll only get an illusion of multiple threads running at the same time via time slicing,
 * nevertheless, but that's fine.  
 * 
 * So the bottom line here is, multithreading is useful in lots of situations. It's particularly
 * useful when you're waiting for something external to happen and you want to run other code at the
 * same time. 
 *
 * It's also useful if you want to distribute some heavy processing across multiple cores in your
 * computer, but then you will only find that you get to speed up if you actually do have multiple
 * cores so that your computer can run multiple threads at the same time. And then you need to know
 * how many threads your hardware can genuinely run genuinely at the same time. 
 */

void work() {
    for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Loop " << i << endl;
    }
}

// Example command: g++ -Wall -std=c++17 -pthread 00_basic_multithreading.cpp && ./a.out
int main() {
    // We can observe that the result is extremely interleaved and mixed up. Thread t1 is running
    // its code essentially at the same time as the thread t2, and that's why we're getting
    // interleaved outputs and we can start lots of threads and run them all at the same time.
    thread t1(work);
    thread t2(work);
    t1.join(); // The function returns when the thread execution has completed.
    t2.join();
    // Output:
    // Loop 0
    // Loop 0
    // Loop 1
    // Loop 1
    // Loop Loop 22
    //
    // Loop 3
    // Loop 3
    // Loop 4
    // Loop 4
    // Loop 5
    // Loop 5
    // Loop 6
    // Loop 6
    // Loop 7
    // Loop 7
    // Loop 8
    // Loop 8
    // Loop 9
    // Loop 9

    return 0;
}
