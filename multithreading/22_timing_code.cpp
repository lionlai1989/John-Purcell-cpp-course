#include <chrono>   // chrono
#include <cmath>    // pow
#include <future>   // shared_future, async, launch
#include <iomanip>  // setprecision
#include <iostream> // cout, endl
#include <thread>   // thread
#include <vector>   // vector

double calculate_pi(int terms, int start, int skip) {
    /**
     * Leibniz formula for pi
     * 1st thread: i=0, 2, 4, 6, 8, ...
     * 2nd thread: i=1, 3, 5, 7, 9, ...
     */
    double sum = 0.0;

    for (int i = start; i < terms; i += skip) {
        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

// g++ -Wall -std=c++17 -pthread 22_timing_code.cpp && ./a.out
int main() {
    /**
     * In this example, we are going to roughly time the code in
     * 21_distributing_work_between_cores.cpp to see what kind of speed up we get from running it in
     * multiple threads.
     */
    std::vector<std::shared_future<double>> futures1;
    std::vector<std::shared_future<double>> futures2;
    const int TERMS = 1E8;

    /**
     * Case 1: Sigle thread
     */
    int CONCURRENCY = 1;
    std::cout << "Threads num: " << CONCURRENCY << std::endl;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < CONCURRENCY; i++) {
        std::shared_future<double> f =
            std::async(std::launch::async, calculate_pi, TERMS, i, CONCURRENCY);
        futures1.push_back(f);
    }

    double sum = 0.0;
    for (auto f : futures1) {
        sum += f.get();
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Duration: " << duration << "ms" << std::endl;
    std::cout << std::setprecision(15) << "PI:  " << M_PI << std::endl;
    std::cout << std::setprecision(15) << "Sum: " << sum << std::endl;
    /**
     * Output:
     * Threads num: 1
     * Duration: 2765ms
     * PI:  3.14159265358979
     * Sum: 3.14159264358933
     *
     * It takes 2765 ms to calculate pi with one thread.
     */

    /**
     * Case 2: Multiple threads
     */
    CONCURRENCY = std::thread::hardware_concurrency();
    std::cout << "Threads num: " << CONCURRENCY << std::endl;

    start = std::chrono::steady_clock::now();

    for (int i = 0; i < CONCURRENCY; i++) {
        std::shared_future<double> f =
            std::async(std::launch::async, calculate_pi, TERMS, i, CONCURRENCY);
        futures2.push_back(f);
    }

    sum = 0.0;
    for (auto f : futures2) {
        sum += f.get();
    }

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Duration: " << duration << "ms" << std::endl;
    std::cout << std::setprecision(15) << "PI:  " << M_PI << std::endl;
    std::cout << std::setprecision(15) << "Sum: " << sum << std::endl;
    /**
     * Output:
     * Threads num: 4
     * Duration: 960ms
     * PI:  3.14159265358979
     * Sum: 3.14159264359661
     *
     * It takes 960 ms to calculate pi with four thread. As you can see, by running 4 threads, which
     * is the number of threads that my computer can genuinely run at the same time, we didn't get a
     * 4 times speed up.
     */

    return 0;
}
