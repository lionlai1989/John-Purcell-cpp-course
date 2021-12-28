#include <iostream>
#include <vector>
using namespace std;

class C {
  public:
    string text;
    int id;
};

struct S {
    string text;
    int id;
};

struct {
    string text;
    int id;
} r1 = {"HelloWorld", 2}, r2 = {"WorldHello", 3};

// Example command: g++ -Wall -std=c++11 -std=gnu++11 c++98_initialization.cpp && ./a.out
int main() {
    int values[] = {1, 3, 5};
    cout << values[0] << endl;
    // 1
    C c1 = {"Hello", 7};
    cout << c1.text << endl;
    // Hello

    S s1 = {"World", 9};
    cout << s1.text << endl;
    // World

    cout << r1.text << endl;
    // HelloWorld
    cout << r2.text << endl;
    // WorldHello

    /**
     * Now that's all well and good, but the use of curly brackets in C++98 is pretty limited.
     * And in particular this is a kind of a bad deficiency in C++98 which is the following. If we
     * run this yes this works fine but such a tedious business of calling push back for all the
     * values in a vector.
     */
    vector<string> strings;
    strings.push_back("One");
    strings.push_back("Two");
    strings.push_back("Three");

    return 0;
}
