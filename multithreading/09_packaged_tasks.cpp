#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <thread>

using namespace std;

double calculate_pi(int terms) {
    /**
     * Leibniz formula for pi
     */
    double sum = 0.0;

    if (terms < 1) {
        throw runtime_error("Terms can not be less than 1");
    }

    for (int i = 0; i < terms; i++) {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

// Example command: g++ -Wall -std=c++17 -pthread 09_packaged_tasks.cpp && ./a.out
int main() {
    /**
     * The class template std::packaged_task wraps any Callable target (function, lambda expression,
     * bind expression, or another function object) so that it can be invoked asynchronously. Its
     * return value or exception thrown is stored in a shared state which can be accessed through
     * std::future objects.   
     */
    packaged_task<double(int)> task1(calculate_pi);
    packaged_task<double(int)> task2(calculate_pi);
    future<double> future1 = task1.get_future();
    future<double> future2 = task2.get_future();

    /**
     * We can not pass task1 with pass by value. We have to pass task1 with pass by reference.
     * Thus, thread t1(ref(task1), 1e6); 
     * 
     * But, we don't need to refer to the "task1" again, we could actually use "move". So move is just
     * saying, look, create a sort of shallow copy of the "task1" and then copy into it any resources 
     * that it's using pointers to memory, whatever, just in fact, just move. So the old one is not
     * necessarily left in a state that's any use. 
     * 
     * std::move is used to indicate that an object t may be "moved from", i.e. allowing the
     * efficient transfer of resources from t to another object.
     */
    thread t1(move(task1), 1e6);
    thread t2(move(task2), 0.5);
    double result1 = future1.get();

    cout << setprecision(15) << result1 << endl; // 3.14159165358977

    try {
        double result2 = future2.get();
        cout << setprecision(15) << result2 << endl;
    } catch (exception &e) {
        cout << "ERROR! " << e.what() << endl;
    } // ERROR! Terms can not be less than 1

    t1.join();
    t2.join();

    return 0;
}
