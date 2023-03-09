#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class String1 {
private:
  uint32_t size;
  char *buffer;

public:
  String1() {
    cout << "Default No-Parameter Constructor" << endl;
    this->size = 0;
    this->buffer = nullptr;
    /**
     * Setting the default value to 0 is a good practice. Three
     * different ways of setting the memory to zero are shown here:
     * memset(_pBuffer, 0, sizeof(int) * SIZE);
     * _pBuffer = new int[SIZE]();
     * _pBuffer = new int[SIZE]{};
     */
  }

  String1(const char *name) {
    cout << "Parameterized Constructor" << endl;
    this->size = std::strlen(name);
    // No need to allocate size+1 buffer. Why?
    this->buffer = new char[this->size];
    memcpy(this->buffer, name, this->size);
  }

  String1(const String1 &other) {
    cout << "Copy Construtor" << endl;
    this->size = other.size;
    this->buffer = new char[this->size];
    memcpy(this->buffer, other.buffer, this->size);
  }

  String1 &operator=(const String1 &other) {
    cout << "Copy Assignment Operator" << endl;
    if (this != &other) {
      // The buffer size of `this` is different from the `other`'s. So we need
      // to delete `this` and reallocate memory for `this` with the size of
      // `other`.
      delete[] this->buffer;

      this->size = other.size;
      this->buffer = new char[this->size];
      memcpy(this->buffer, other.buffer, this->size);
    }
    return *this;
  }

  ~String1() {
    cout << "Destructor: ";
    for (uint32_t i = 0; i < this->size; ++i) {
      cout << this->buffer[i];
    }
    cout << '\n';
    delete[] this->buffer;
  }

  friend ostream &operator<<(ostream &out, const String1 &test);
};

ostream &operator<<(ostream &out, const String1 &test) {
  out << "String: ";
  for (uint32_t i = 0; i < test.size; ++i) {
    out << test.buffer[i] << ' ';
  }
  return out;
}

String1 get_String1() { return String1(); }

class String2 {
private:
  uint32_t size;
  char *buffer;

public:
  String2() {
    cout << "Default No-Parameter Constructor" << endl;
    this->size = 0;
    this->buffer = nullptr;
  }

  String2(const char *name) {
    cout << "Parameterized Constructor" << endl;
    this->size = std::strlen(name);
    this->buffer = new char[this->size];
    memcpy(this->buffer, name, this->size);
  }

  String2(const String2 &other) {
    cout << "Copy Construtor" << endl;
    this->size = other.size;
    this->buffer = new char[this->size];
    memcpy(this->buffer, other.buffer, this->size);
  }

  String2 &operator=(const String2 &other) {
    cout << "Copy Assignment Operator" << endl;
    if (this != &other) {
      // The buffer size of `this` is different from the `other`'s. So we need
      // to delete `this` and reallocate memory for `this` with the size of
      // `other`.
      delete[] this->buffer;

      this->size = other.size;
      this->buffer = new char[this->size];
      memcpy(this->buffer, other.buffer, this->size);
    }
    return *this;
  }

  String2(String2 &&other) {
    cout << "Move Constructor" << endl;
    this->size = other.size;
    /**
     * In the copy constructor, we have to allocate memory.
     * In the move constructor, we don't have to allocate any more memory. We
     * just have to change a couple of variables so it's very efficient.
     */
    this->buffer = other.buffer;

    /**
     * NOTE: Here, the destructor of "other" will deallocate "other.buffer" and
     * we've stolen the buffer so we don't want that to happen. So to deal
     * with this all we have to do is set "other.buffer" to point to
     * nullptr. And it is safe to delete a nullptr.
     */
    other.size = 0;
    other.buffer = nullptr;
  }

  String2 &operator=(String2 &&other) {
    cout << "Move Assignment Operator" << endl;
    if (this != &other) {
      this->size = other.size;
      /**
       * Here, the object `buffer` to which `this` points, needs to be freed up,
       * because `this` is going to point to `other`'s memory. If it's not done,
       * then we have a memory leak.
       */
      delete[] this->buffer;

      this->buffer = other.buffer;

      other.size = 0;
      other.buffer = nullptr;
    }
    return *this;
  }
  ~String2() {
    cout << "Destructor: ";
    // NOTE: a potential bug is here. If `this` has pointed to a nullptr and
    // size is non-zero, then it causes error:
    // Segmentation fault (core dumped)
    for (uint32_t i = 0; i < this->size; ++i) {
      cout << this->buffer[i];
    }
    cout << '\n';
    delete[] this->buffer;
  }

  friend ostream &operator<<(ostream &out, const String2 &test);
};

ostream &operator<<(ostream &out, const String2 &test) {
  out << "String: ";
  for (uint32_t i = 0; i < test.size; ++i) {
    out << test.buffer[i] << ' ';
  }
  return out;
}

String2 get_String2() { return String2(); }

// Example command:
// g++ -Wall -std=c++17 -std=gnu++17 constructors_and_assignment_operators.cpp && ./a.out
int main() {
  // Comment out the code below to run the test.

  // String1 test1;
  // test1 = get_String1();
  // String1 test2{"test2"};
  // String1 test3{test2};
  // cout << "test1: " << test1 << endl;
  // test1 = test3;
  // cout << "test2: " << test2 << endl;
  // cout << "test3: " << test3 << endl;
  // cout << "test1: " << test1 << endl;
  // vector<String1> vec;
  // vec.push_back(String1("rvalue"));
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

  // String2 test1;
  // test1 = get_String2();
  // String2 test2{"test2"};
  // String2 test3{test2};
  // cout << "test1: " << test1 << endl;
  // test1 = test3;
  // cout << "test2: " << test2 << endl;
  // cout << "test3: " << test3 << endl;
  // cout << "test1: " << test1 << endl;
  // vector<String2> vec;
  // vec.push_back(String2("rvalue"));
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

  // cout << "Test move-from object\n";
  // String2 test1{"apple"};
  // String2 test2;
  // cout << test1 << '\n';
  // cout << test2 << '\n';
  // test2 = std::move(test1);
  // cout << test1 << '\n';
  // cout << test2 << '\n';

  return 0;
}
