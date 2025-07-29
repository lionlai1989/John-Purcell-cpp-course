#include <cmath>
#include <iomanip>
#include <iostream>

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

// g++ -Wall -std=c++17 -pthread 06_calculating_pi.cpp && ./a.out
int main() {
    std::cout << std::setprecision(15) << calculate_pi(1e6) << std::endl;

    return 0;
}
