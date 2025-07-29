#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <thread>

double calculate_pi(int terms) {
    /**
     * Leibniz formula for pi
     */
    double sum = 0.0;

    for (int i = 0; i < terms; i++) {
        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

// g++ -Wall -std=c++17 -pthread 07_promises_and_futures.cpp && ./a.out
int main() {
    /**
     * The promise is something like the producer, which is used to carry the result that it
     * creates.
     */
    std::promise<double> promise;

    auto do_calculation = [&](int terms) {
        auto result = calculate_pi(terms);

        // Set the result into the promise.
        promise.set_value(result);
    };

    std::thread t1(do_calculation, 1e6);

    /**
     * On the consumer side, the side that gets the result does something with it. We've got a
     * future which we get from the promise and then we call get() on the future to get the result
     * and get() is a blocking function. So "future.get()" won't return until you do
     * "promise.set_value(result);" in the thread. And that's why it probably doesn't matter even if
     * we put "t1.join();" down here, because this is going to wait until "future.get()" happens
     * anyway.
     */
    std::future<double> future = promise.get_future();
    std::cout << std::setprecision(15) << future.get() << std::endl;

    /**
     * "t1.join();" is still here. Otherwise there will be the error below.
     * terminate called without an active exception
     * Aborted (core dumped)
     */
    t1.join();

    return 0;
}
