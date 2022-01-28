#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/**
 * A callable object is an object of a class that overloads the call operator "()".
 */
class App {
  private:
    int count = 0;
    mutex mtx;

  public:
    void operator()() {
        for (int i = 0; i < 1e6; i++) {
            lock_guard<mutex> guard(mtx);
            ++count;
        }
    }

    int get_count() {
        return count;
    }
};

// Example command: g++ -Wall -std=c++17 -pthread 05_threads_with_callable_objects.cpp && ./a.out
int main() {
    App app;
    app();

    thread t1(ref(app)); // Pass the reference wrapper object with which thread can work.
    thread t2(ref(app));

    t1.join();
    t2.join();

    /**
     * The output 3000000 is comprised of app(), thread t1(ref(app)), thread t2(ref(app)).
     */
    cout << app.get_count() << endl; // 3000000
    return 0;
}
