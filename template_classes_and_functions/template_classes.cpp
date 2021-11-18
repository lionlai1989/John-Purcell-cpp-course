#include <iostream>

using namespace std;

// The template class should be in the header file. It is put here for the sake of convenience.
// "T" and k are just a symbol here. They can be anything like "helloworld".
// "obj" is just a variable name.
template <class T, class K>
class Test {
  private:
    T obj;

  public:
    Test(T obj) {
        this->obj = obj;
    }
    void print() {
        cout << obj << endl;
    }
};

// Example command: g++ -Wall template_classes.cpp && ./a.out
int main() {
    Test<string, int> test1("Hello");
    test1.print();
    return 0;
}
