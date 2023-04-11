#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

bool check(string &test) {
    return test.size() == 3;
}

class Check {
  public:
    bool operator()(string &test) {
        return test.size() == 3;
    }
} check1;

/**
 * check represents a bunch of callable things which accepts a string and returns a boolean.
 */
void run(function<bool(string &)> check, string &test_string) {
    cout << check(test_string) << endl;
}

// Example command: g++ -Wall -std=c++11 -std=gnu++11 functional_types.cpp && ./a.out
int main() {
    int size = 3;
    vector<string> vec_str = {"one", "two", "three"};

    /**
     * count_if() returns the number of elements in the range [first, last) satisfying specific criteria.
     * 1) counts the elements that are equal to value.
     * 3) counts elements for which predicate p returns true.
     */
    int count = count_if(vec_str.begin(),
                         vec_str.end(),
                         [size](string test) {
                             return test.size() == size;
                         });
    cout << count << endl; // 2. "one" and "two" are size 3.

    count = count_if(vec_str.begin(),
                     vec_str.end(),
                     check);
    cout << count << endl; // 2

    count = count_if(vec_str.begin(),
                     vec_str.end(),
                     check1);
    cout << count << endl; // 2

    auto lambda = [size](string test) { return test.size() == size; };
    string test_string = "dog";
    run(lambda, test_string); // 1. lambda checks if test_string == 3.
    run(check1, test_string); // 1. check1 checks if test_string == 3.
    run(check, test_string);  // 1. check checks if test_string == 3.

    /**
     * add() is a function type which adds up two integers and returns the result (integer).
     */
    function<int(int, int)> add = [](int one, int two) { return one + two; };
    cout << add(3, 7) << endl;
    return 0;
}
