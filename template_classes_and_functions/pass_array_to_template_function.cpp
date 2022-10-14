#include <iostream>

void printarray (int arg[], int length) {
    for (int n = 0; n < length; n++) {
        std::cout << arg[n] << " ";
    }
    std::cout << "\n";
}

void print_fixed_array (int (&arg)[3]) {
    for (auto n : arg) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

template<typename T, std::size_t S>
void print_variable_array(T (&arr)[S]) {
    for (auto n : arr) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 pass_array_to_function.cpp && ./a.out
int main ()
{
    int firstarray[] = {5, 10, 15};
    int secondarray[] = {2, 4, 6, 8, 10};

    printarray(firstarray, 3);
    printarray(secondarray, 5);

    print_fixed_array(firstarray);
    // print_fixed_array(secondarray); <- This line has the following error:
    // pass_array_to_function.cpp: In function ‘int main()’:
    // pass_array_to_function.cpp:33:24: error: invalid initialization of reference of type ‘int (&)[3]’ from expression of type ‘int [5]’
    // 33 |      print_fixed_array(secondarray);
    //    |                        ^~~~~~~~~~~
    // pass_array_to_function.cpp:10:31: note: in passing argument 1 of ‘void print_fixed_array(int (&)[3])’
    // 10 | void print_fixed_array (int (&arg)[3]) {
    //    |                         ~~~~~~^~~~~~~

    print_variable_array(firstarray);
    print_variable_array(secondarray);

    return 0;
}
