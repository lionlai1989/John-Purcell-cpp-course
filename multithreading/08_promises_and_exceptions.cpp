#include <cmath>
#include <exception>
#include <future>
#include <iomanip>
#include <iostream>
#include <thread>

double calculate_pi(int terms) {
    /**
     * Leibniz formula for pi
     */
    double sum = 0.0;

    if (terms < 1) {
        throw std::runtime_error("Terms can not be less than 1");
    }

    for (int i = 0; i < terms; i++) {
        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

// g++ -Wall -std=c++17 -pthread 08_promises_and_exceptions.cpp && ./a.out
int main() {
    /**
     * In this tutorial, we're going to look at how exceptions work with promises. Naturally, it's
     * possible that you may be calculating something in the thread, and something may go wrong, and
     * it may throw an exception. And in that case, the question arises how to signal when you
     * actually get the result from the future that there isn't a result and instead there's only an
     * exception.
     */
    std::promise<double> promise;

    auto do_calculation = [&](int terms) {
        try {
            auto result = calculate_pi(terms);
            promise.set_value(result);
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            promise.set_exception(std::current_exception());
        }
    };

    std::thread t1(do_calculation, 0);

    std::future<double> future = promise.get_future();

    try {
        std::cout << std::setprecision(15) << future.get() << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    t1.join();

    return 0;
}
