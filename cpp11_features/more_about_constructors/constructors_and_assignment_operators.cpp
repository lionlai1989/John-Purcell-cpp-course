#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test1 {
private:
  static const int SIZE = 10;
  int *_pBuffer;
  string name;

public:
  Test1() {
    cout << "Default No-Parameter Constructor" << endl;
    this->_pBuffer = new int[SIZE]{};
    this->name = "default";
    /**
     * Setting the default value to 0 is a good practice. Three
     * different ways of setting the memory to zero are shown here:
     * memset(_pBuffer, 0, sizeof(int) * SIZE);
     * _pBuffer = new int[SIZE]();
     * _pBuffer = new int[SIZE]{};
     */
  }

  Test1(int i, string name) {
    cout << "Parameterized Constructor" << endl;
    this->name = name;
    this->_pBuffer = new int[this->SIZE]{};
    for (int j = 0; j < this->SIZE; j++) {
      this->_pBuffer[j] = i * i;
    }
  }

  Test1(const Test1 &other) {
    cout << "Copy Construtor" << endl;
    this->name = other.name;
    this->_pBuffer = new int[this->SIZE]{};
    memcpy(this->_pBuffer, other._pBuffer, sizeof(int) * this->SIZE);
  }

  Test1 &operator=(const Test1 &other) {
    cout << "Copy Assignment Operator" << endl;
    this->name = other.name;
    memcpy(this->_pBuffer, other._pBuffer, sizeof(int) * this->SIZE);
    return *this;
  }

  ~Test1() {
    cout << "Destructor: "
         << "Destroy " << this->name << endl;
    delete[] this->_pBuffer;
  }

  friend ostream &operator<<(ostream &out, const Test1 &test);
};

ostream &operator<<(ostream &out, const Test1 &test) {
  out << "Elements: ";
  for (int i = 0; i < test.SIZE; ++i) {
    out << test._pBuffer[i] << ' ';
  }
  return out;
}

Test1 get_test1() { return Test1(); }

class Test2 {
private:
  static const int SIZE = 10;
  int *_pBuffer;
  string name;

public:
  Test2() {
    cout << "Default No-Parameter Constructor" << endl;
    this->_pBuffer = new int[SIZE]{};
    this->name = "default";
  }

  Test2(int i, string name) {
    cout << "Parameterized Constructor" << endl;
    this->name = name;
    this->_pBuffer = new int[this->SIZE]{};
    for (int j = 0; j < this->SIZE; j++) {
      this->_pBuffer[j] = i * i;
    }
  }

  Test2(const Test2 &other) {
    cout << "Copy Construtor" << endl;
    this->name = other.name;
    this->_pBuffer = new int[this->SIZE]{};
    memcpy(this->_pBuffer, other._pBuffer, sizeof(int) * this->SIZE);
  }

  Test2 &operator=(const Test2 &other) {
    cout << "Copy Assignment Operator" << endl;
    this->name = other.name;
    memcpy(this->_pBuffer, other._pBuffer, sizeof(int) * this->SIZE);
    return *this;
  }

  Test2(Test2 &&other) {
    cout << "Move Constructor" << endl;
    this->name = other.name;
    /**
     * In the copy constructor, we have to allocate memory.
     * In the move constructor, we don't have to allocate any more memory. We
     * just have to change a couple of variables so it's very efficient.
     */
    this->_pBuffer = other._pBuffer;

    /**
     * NOTE: Here, the destructor of "other" will deallocate "_pBuffer" and
     * we've stolen the buffer so we don't want that to happen. So to deal with
     * this all we have to do is set "other._pBuffer" to point to nullptr. And
     * it is safe to delete a nullptr.
     */
    other._pBuffer = nullptr;
  }

  Test2 &operator=(Test2 &&other) {
    cout << "Move Assignment Operator" << endl;
    this->name = other.name;
    /**
     * Here, the object to which we are assigning, already allocated
     * memory. So, we need to free up any memory that has been
     * allocated.
     */
    delete[] this->_pBuffer;

    this->_pBuffer = other._pBuffer;

    other._pBuffer = nullptr;

    return *this;
  }

  ~Test2() {
    cout << "Destructor: "
         << "Destroy " << this->name << endl;
    delete[] this->_pBuffer;
  }

  friend ostream &operator<<(ostream &out, const Test2 &test);
};

ostream &operator<<(ostream &out, const Test2 &test) {
  out << "Elements: ";
  for (int i = 0; i < test.SIZE; ++i) {
    out << test._pBuffer[i] << ' ';
  }
  return out;
}

Test2 get_test2() { return Test2(); }

// Example command:
// g++ -Wall -std=c++17 -std=gnu++17 constructors_and_memory.cpp && ./a.out
int main() {
  // Test1 test1;
  // test1 = get_test1();
  // Test1 test2{1, "test2"};
  // Test1 test3{test2};
  // cout << "test1: " << test1 << endl;
  // test1 = test3;
  // cout << "test2: " << test2 << endl;
  // cout << "test3: " << test3 << endl;
  // cout << "test1: " << test1 << endl;
  // vector<Test1> vec;
  // vec.push_back(Test1(10, "rvalue"));
  // vec.push_back(test1);
  // cout << "vec[0] " << vec[0] << endl;
  // cout << "vec[1] " << vec[1] << endl;
  /** The output message:
  Default No-Parameter Constructor
  Default No-Parameter Constructor
  Copy Assignment Operator
  Destructor: Destroy default
  Parameterized Constructor
  Copy Construtor
  test1: Elements: 0 0 0 0 0 0 0 0 0 0
  Copy Assignment Operator
  test2: Elements: 1 1 1 1 1 1 1 1 1 1
  test3: Elements: 1 1 1 1 1 1 1 1 1 1
  test1: Elements: 1 1 1 1 1 1 1 1 1 1
  Parameterized Constructor
  Copy Construtor
  Destructor: Destroy rvalue
  Copy Construtor
  Copy Construtor
  Destructor: Destroy rvalue
  vec[0] Elements: 100 100 100 100 100 100 100 100 100 100
  vec[1] Elements: 1 1 1 1 1 1 1 1 1 1
  Destructor: Destroy rvalue
  Destructor: Destroy test2
  Destructor: Destroy test2
  Destructor: Destroy test2
  Destructor: Destroy test2
  **/

  // Test2 test1;
  // test1 = get_test2();
  // Test2 test2{1, "test2"};
  // Test2 test3{test2};
  // cout << "test1: " << test1 << endl;
  // test1 = test3;
  // cout << "test2: " << test2 << endl;
  // cout << "test3: " << test3 << endl;
  // cout << "test1: " << test1 << endl;
  // vector<Test2> vec;
  // vec.push_back(Test2(10, "rvalue"));
  // vec.push_back(test1);
  // cout << "vec[0] " << vec[0] << endl;
  // cout << "vec[1] " << vec[1] << endl;
  /** The output message:
  Default No-Parameter Constructor
  Default No-Parameter Constructor
  Move Assignment Operator
  Destructor: Destroy default
  Parameterized Constructor
  Copy Construtor
  test1: Elements: 0 0 0 0 0 0 0 0 0 0
  Copy Assignment Operator
  test2: Elements: 1 1 1 1 1 1 1 1 1 1
  test3: Elements: 1 1 1 1 1 1 1 1 1 1
  test1: Elements: 1 1 1 1 1 1 1 1 1 1
  Parameterized Constructor
  Move Constructor
  Destructor: Destroy rvalue
  Copy Construtor
  Copy Construtor
  Destructor: Destroy rvalue
  vec[0] Elements: 100 100 100 100 100 100 100 100 100 100
  vec[1] Elements: 1 1 1 1 1 1 1 1 1 1
  Destructor: Destroy rvalue
  Destructor: Destroy test2
  Destructor: Destroy test2
  Destructor: Destroy test2
  Destructor: Destroy test2
  **/

  return 0;
}
