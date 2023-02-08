#include <src/matrix/matrix.hpp>
#include <iostream>

void print_fixed_array (int (&arg)[3]) {
    for (auto n : arg) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}
