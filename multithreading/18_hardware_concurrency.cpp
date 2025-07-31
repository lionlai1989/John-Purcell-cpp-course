#include <iostream>
#include <thread>

// g++ -Wall -std=c++17 -pthread 18_hardware_concurrency.cpp && ./a.out
int main() {
    /**
     * In this tutorial, we are finding out how many threads we can genuinely run at the same time.
     *
     * std::thread::hardware_concurrency
     * static unsigned int hardware_concurrency() noexcept;
     * Returns the number of concurrent threads supported by the implementation. The value should be
     * considered only a hint.
     */

    std::cout << std::thread::hardware_concurrency() << std::endl;
    /**
     * The output shows 4 but do not trust the number shown here. Try number of threads to see what
     * number works best for an application.
     * Output:
     * 4
     */
    return 0;
}
