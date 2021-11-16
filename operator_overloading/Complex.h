#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <iostream>

using namespace std;

namespace caveofprogramming {

class Complex {
  private:
    double real;
    double imaginary;

  public:
    Complex();
    Complex(double real, double imaginary);
    Complex(const Complex &other);
    const Complex &operator=(const Complex &other);

    // "get_real()" and "get_imaginary()" are public functions. c++ does not know if the object
    // iself that called on will be changed so that const must be added here.
    // Eg, "ostream &operator<<(ostream &out, const Complex &c)" in Complex.cpp calls "c.get_real()"
    // and "c.get_imaginary()", and the object "c" shall not be changed while calling its public
    // functions, thus const shall be added here.
    double get_real() const {
        return real;
    }
    double get_imaginary() const {
        return imaginary;
    }

    bool operator==(const Complex &other) const;
    bool operator!=(const Complex &other) const;

    // Implement the conjugate of a complex number for the fun sake.
    Complex operator*() const;
};

// Prototype of the left-bit-shift operator.
ostream &operator<<(ostream &out, const Complex &c);

// Prototype of the plus operator. We cannot add const in the end like
// "Complex operator+(const Complex &c1, const Complex &c2) const;", because it is a free standing
// function, not a method.
Complex operator+(const Complex &c1, const Complex &c2);

// Prototype of another plus operator which takes in real-numbers only.
Complex operator+(const Complex &c1, double d);
Complex operator+(double d, const Complex &c1);

} // namespace caveofprogramming

#endif
