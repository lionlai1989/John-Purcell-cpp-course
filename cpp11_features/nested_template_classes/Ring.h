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
  public:
    class iterator;
};

template <typename T>
class Ring<T>::iterator {
  public:
    void print() {
        cout << "Hello from iterator: " << T() << endl;
    };
};

#endif
