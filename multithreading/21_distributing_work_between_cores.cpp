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

// Example command: g++ -Wall -std=c++17 -pthread 21_distributing_work_between_cores.cpp && ./a.out
int main() {
    /**
     * In this example, we're going to take a look at an actual example of using multiple cores to
     * process some CPU intensive work, calculating PI.
     */
    vector<shared_future<double>> futures;

    const int CONCURRENCY = thread::hardware_concurrency();

    for (int i = 0; i < CONCURRENCY; i++) {
        shared_future<double> f = async(launch::async, calculate_pi, 1E7, i, CONCURRENCY);
        futures.push_back(f);
    }

    double sum = 0.0;
    for (auto f : futures) {
        sum += f.get();
    }

    cout << setprecision(15) << "PI:  " << M_PI << endl; // const from cmath
    cout << setprecision(15) << "Sum: " << sum << endl;  // calculated pi
    /**
     * Output:
     * PI:  3.14159265358979
     * Sum: 3.14159255359074
     * 
     * The multithreads work. We can set 1E7 to a bigger number to calculate more accurate pi.
     */
    return 0;
}
