#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool match(string test) {
    return test.size() == 3;
}

int count_strings(vector<string> &texts, bool (*match)(string test)) {
    // Implement our version of count_if, which can check the strings in a vector.
    // "vector<string> &texts": a reference to a vector of strings.
    // "bool (*match)(string test)": "match" is a function pointer, which can point to a funtion
    // that returns a boolean and takes an argument of string.

    int tally = 0;
    for (int i = 0; i < texts.size(); i++) {
        if (match(texts[i])) {
            tally++;
        }
    }

    return tally;
}

// Example command: g++ -Wall using_function_pointers.cpp && ./a.out
int main() {
    vector<string> texts;
    texts.push_back("one");
    texts.push_back("two");
    texts.push_back("three");
    texts.push_back("two");
    texts.push_back("four");
    texts.push_back("two");
    texts.push_back("three");

    cout << match("one") << endl; // 1

    cout << count_if(texts.begin(), texts.end(), match) << endl; // 4
    // "texts.begin()": Pass an iterator to the start of the range.
    // "texts.end()": Pass an iterator to the end of the range.
    // "match": Pass a function that returns True or False.

    // count_strings is our version of count_if.
    cout << count_strings(texts, match) << endl; // 4
    return 0;
}
