#ifndef RING_H_
#define RING_H_

#include <iostream>
using namespace std;

/**
 * It's not a good practice. The reason is that the code looks ugly if nested level is too deep.
 * class Ring {
 *   public:
 *     class iterator {
 *       public:
 *         void print() {
 *             cout << "Hello from iterator" << endl;
 *         }
 *     };
 * };
 *
 */

template <typename T>
class Ring {
  private:
    int m_pos;
    int m_size;
    T *m_values;

  public:
    class iterator;

  public:
    // The order of initialization should be the same of the order of declaration.
    Ring(int size) : m_pos(0), m_size(size), m_values(NULL) {
        m_values = new T[size];
    }
    ~Ring() {
        delete[] m_values;
    }
    int size() {
        return m_size;
    }
    void add(T value) {
        m_values[m_pos] = value;
        m_pos++;
        if (m_pos == m_size) {
            m_pos = 0;
        }
    }
    T &get(int pos) {
        // The return value is a reference to an element in a ring buffer. Conventionally, the STL
        // will return a reference to the value in a c++ container (list, vector, array, etc.).
        return m_values[pos];
    }
};

template <typename T>
class Ring<T>::iterator {
  public:
    void print() {
        cout << "Hello from iterator: " << T() << endl;
    };
};

#endif
