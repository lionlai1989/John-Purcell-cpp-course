#include <chrono>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

double calculate_pi(int terms, int start, int skip) {
    /**
     * Leibniz formula for pi
     * 1st thread: i=0, 2, 4, 6, 8, ...
     * 2nd thread: i=1, 3, 5, 7, 9, ...
     */
    double sum = 0.0;

    for (int i = start; i < terms; i += skip) {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

// Example command: g++ -Wall -std=c++17 -pthread 22_timing_code.cpp && ./a.out
int main() {
    /**
     * In this example, we are going to roughly time the code in
     * 21_distributing_work_between_cores.cpp to see what kind of speed up we get from running it in
     * multiple threads. 
     */
    vector<shared_future<double>> futures1;
    vector<shared_future<double>> futures2;
    const int TERMS = 1E8;

    /**
     * Case 1: Sigle thread
     */
    int CONCURRENCY = 1;
    cout << "Threads num: " << CONCURRENCY << endl;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < CONCURRENCY; i++) {
        shared_future<double> f = async(launch::async, calculate_pi, TERMS, i, CONCURRENCY);
        futures1.push_back(f);
    }

    double sum = 0.0;
    for (auto f : futures1) {
        sum += f.get();
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Duration: " << duration << "ms" << endl;
    cout << setprecision(15) << "PI:  " << M_PI << endl;
    cout << setprecision(15) << "Sum: " << sum << endl;
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
    CONCURRENCY = thread::hardware_concurrency();
    cout << "Threads num: " << CONCURRENCY << endl;

    start = chrono::steady_clock::now();

    for (int i = 0; i < CONCURRENCY; i++) {
        shared_future<double> f = async(launch::async, calculate_pi, TERMS, i, CONCURRENCY);
        futures2.push_back(f);
    }

    sum = 0.0;
    for (auto f : futures2) {
        sum += f.get();
    }

    end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Duration: " << duration << "ms" << endl;
    cout << setprecision(15) << "PI:  " << M_PI << endl;
    cout << setprecision(15) << "Sum: " << sum << endl;
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
