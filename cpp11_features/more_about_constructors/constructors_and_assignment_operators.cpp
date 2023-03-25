#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class String1 {
private:
  uint32_t size;
  char *buffer;

public:
  String1() {
    std::cout << "Default No-Parameter Constructor\n";
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
    std::cout << "Parameterized Constructor\n";
    this->size = std::strlen(name);
    // No need to allocate size+1 buffer. Why?
    this->buffer = new char[this->size];
    memcpy(this->buffer, name, this->size);
  }

  String1(const String1 &other) {
    std::cout << "Copy Construtor\n";
    this->size = other.size;
    this->buffer = new char[this->size];
    memcpy(this->buffer, other.buffer, this->size);
  }

  String1 &operator=(const String1 &other) {
    std::cout << "Copy Assignment Operator\n";
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
    std::cout << "Destructor: ";
    for (uint32_t i = 0; i < this->size; ++i) {
      std::cout << this->buffer[i];
    }
    std::cout << '\n';
    delete[] this->buffer;
  }

  friend std::ostream &operator<<(std::ostream &out, const String1 &test);
};

std::ostream &operator<<(std::ostream &out, const String1 &test) {
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
    std::cout << "Default No-Parameter Constructor\n";
    this->size = 0;
    this->buffer = nullptr;
  }

  String2(const char *name) {
    std::cout << "Parameterized Constructor\n";
    this->size = std::strlen(name);
    this->buffer = new char[this->size];
    memcpy(this->buffer, name, this->size);
  }

  String2(const String2 &other) {
    std::cout << "Copy Construtor\n";
    this->size = other.size;
    this->buffer = new char[this->size];
    memcpy(this->buffer, other.buffer, this->size);
  }

  String2 &operator=(const String2 &other) {
    std::cout << "Copy Assignment Operator\n";
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
    std::cout << "Move Constructor\n";
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
    std::cout << "Move Assignment Operator\n";
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
    std::cout << "Destructor: ";
    // NOTE: a potential bug is here. If `this` has pointed to a nullptr and
    // size is non-zero, then it causes error:
    // Segmentation fault (core dumped)
    for (uint32_t i = 0; i < this->size; ++i) {
      std::cout << this->buffer[i];
    }
    std::cout << '\n';
    delete[] this->buffer;
  }

  friend std::ostream &operator<<(std::ostream &out, const String2 &test);
};

std::ostream &operator<<(std::ostream &out, const String2 &test) {
  out << "String: ";
  for (uint32_t i = 0; i < test.size; ++i) {
    out << test.buffer[i] << ' ';
  }
  return out;
}

String2 get_String2() { return String2(); }

class String3 {
private:
  /**
   * Does the order of declaration matter?
   */
  std::size_t size = 0;
  char *buffer = nullptr;

public:
  String3() : size{0}, buffer{nullptr} {
    std::clog << "Default No-Parameter Constructor\n";
  }

  String3(const char *name) : size{std::strlen(name)}, buffer{new char[size]} {
    /**
     * Pay attention to the order of the initialization.
     */
    std::clog << "Parameterized Constructor\n";
    memcpy(this->buffer, name, this->size);
  }

  String3(const String3 &other) : size{other.size}, buffer{new char[size]} {
    /**
     * Pay attention to the order of the initialization.
     */
    std::clog << "Copy Construtor\n";
    memcpy(this->buffer, other.buffer, this->size);
  }

  String3 &operator=(const String3 &other) {
    std::clog << "Copy Assignment Operator\n";
    if (this != &other) {
      delete[] this->buffer;

      this->size = other.size;
      this->buffer = new char[this->size];
      memcpy(this->buffer, other.buffer, this->size);
    }
    return *this;
  }

  String3(String3 &&other) {
    std::cout << "Move Constructor\n";
    swap(other);
  }

  String3 &operator=(String3 &&other) {
    std::cout << "Move Assignment Operator\n";
    swap(other);
    /**
     * Is it necessary to reset `other.size` and `other.buffer` as below?
     * other.size = 0;
     * other.buffer = nullptr;
     * If these two values are not reset, the moved-from object will still hold
     * the original before-moved value of `this`. In theory, you SHOULDN'T CARE
     * because you SHOULDN'T USE the moved-from object anymore.
     */
    return *this;
  }

  void swap(String3 &other) {
    std::swap(this->size, other.size);
    std::swap(this->buffer, other.buffer);
  }

  ~String3() {
    std::cout << "Destructor: ";
    for (uint32_t i = 0; i < this->size; ++i) {
      std::cout << this->buffer[i];
    }
    std::cout << '\n';
    delete[] this->buffer;
  }

  friend std::ostream &operator<<(std::ostream &out, const String3 &test);
};

std::ostream &operator<<(std::ostream &out, const String3 &test) {
  out << "String: ";
  for (uint32_t i = 0; i < test.size; ++i) {
    out << test.buffer[i] << ' ';
  }
  return out;
}

String3 get_String3() { return String3(); }

// Example command:
// g++ -Wall -std=c++17 -std=gnu++17 constructors_and_assignment_operators.cpp && ./a.out
int main() {
  /**
   * Comment out the code below to run the test.
   */

  /**
   * String1 does not have customized move constructor and move assignment
   * operator. Observe the behaviour and explain what you see.
   */
  // String1 test1;
  // test1 = get_String1();
  // String1 test2{"test2"};
  // String1 test3{test2};
  // std::cout << "test1: " << test1 << '\n';
  // test1 = test3;
  // std::cout << "test2: " << test2 << '\n';
  // std::cout << "test3: " << test3 << '\n';
  // std::cout << "test1: " << test1 << '\n';
  // std::vector<String1> vec;
  // vec.push_back(String1("rvalue"));
  // vec.push_back(test1);
  // std::cout << "vec[0] " << vec[0] << '\n';
  // std::cout << "vec[1] " << vec[1] << '\n';
  // std::cout << '\n';

  // std::cout << "Test move-from object:\n";
  // test2 = std::move(test1);
  // std::cout << "test2: " << test2 << '\n';
  // std::cout << "test1: " << test1 << '\n';

  /**
   * String2 has customized move constructor and move assignment
   * operator. Observe the behaviour and explain what you see.
   */
  // String2 test1;
  // test1 = get_String2();
  // String2 test2{"test2"};
  // String2 test3{test2};
  // std::cout << "test1: " << test1 << '\n';
  // test1 = test3;
  // std::cout << "test2: " << test2 << '\n';
  // std::cout << "test3: " << test3 << '\n';
  // std::cout << "test1: " << test1 << '\n';
  // std::vector<String2> vec;
  // vec.push_back(String2("rvalue"));
  // vec.push_back(test1);
  // std::cout << "vec[0] " << vec[0] << '\n';
  // std::cout << "vec[1] " << vec[1] << '\n';
  // std::cout << '\n';

  // std::cout << "Test move-from object:\n";
  // test2 = std::move(test1);
  // std::cout << "test2: " << test2 << '\n';
  // std::cout << "test1: " << test1 << '\n';

  /**
   * String3 also has customized move constructor and move assignment
   * operator and the implementation of String3 is optimized by following the
   * suggestions in this codereview:
   * https://codereview.stackexchange.com/questions/283826/a-simple-string-class-and-its-special-member-functions
   * Compare the output message between String2 and String3 to see if there is
   * any discrepancy. If there is any discrepancy, investigate String2 and
   * String3 carefully to see if you can explain the root cause of the
   * phenomenon. Hint: swap() in move assignment operator doesn't reset objects.
   */
  // String3 test1;
  // test1 = get_String3();
  // std::cout << "Observe RVO (Return Value Optimization) and Copy Elision."
  //           << test1 << '\n';
  // std::cout << '\n';
  // String3 test2{"test2"};
  // String3 test3{test2};
  // std::cout << "test1: " << test1 << '\n';
  // test1 = test3;
  // std::cout << "test2: " << test2 << '\n';
  // std::cout << "test3: " << test3 << '\n';
  // std::cout << "test1: " << test1 << '\n';
  // std::vector<String3> vec;
  // vec.push_back(String3("rvalue"));
  // vec.push_back(test1);
  // std::cout << "vec[0] " << vec[0] << '\n';
  // std::cout << "vec[1] " << vec[1] << '\n';
  // std::cout << '\n';

  // std::cout << "Test move-from object:\n";
  // test2 = std::move(test1);
  // std::cout << "test2: " << test2 << '\n';
  // std::cout << "test1: " << test1 << '\n';

  // std::cout << "\nTest move-from object\n";
  // String3 test_apple{"apple"};
  // String3 test_empty{"orange"};
  // std::cout << test_apple << '\n';
  // std::cout << test_empty << '\n';
  // test_empty = std::move(test_apple);
  // std::cout << test_apple << '\n';
  // std::cout << test_empty << '\n';

  return 0;
}
