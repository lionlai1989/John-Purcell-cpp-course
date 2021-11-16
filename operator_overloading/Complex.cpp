#include "Complex.h"

namespace caveofprogramming {

Complex operator+(double d, const Complex &c1) {
    return Complex(c1.get_real() + d, c1.get_imaginary());
}
Complex operator+(const Complex &c1, double d) {
    // Implementation of another plus operator.
    // "double d": it could also be "double &d", but it is just a matter of few bytes, so does not
    // really matter if it copies the value or uses the reference.
    // It only takes the statment of the Complex object on the left side and double object on the
    // right side. Eg, c5 = c4 + 7;. It does not work in the reverse order. Eg, c5 = 7 + c4;. Thus,
    // we should also implement another operator+ which takes the reverse order.
    return Complex(c1.get_real() + d, c1.get_imaginary());
}

Complex operator+(const Complex &c1, const Complex &c2) {
    // Implementation of the plus operator.
    // "Complex operator+": It deos not return a reference, but a brand new number.
    // c1 and c2 are const references whose values cannot be changed.
    return Complex(c1.get_real() + c2.get_real(), c1.get_imaginary() + c2.get_imaginary());
}

ostream &operator<<(ostream &out, const Complex &c) {
    // Implementation of the left-bit-shift operator.
    // It is a function, not a method.

    // "c.get_real()" and "c.get_imaginary()" are public functions.
    out << "(" << c.get_real() << "," << c.get_imaginary() << ")";
    return out;
}

Complex::Complex() : real(0), imaginary(0) {
    // TODO: Auto-generated constructor stub
    // Complex c1; in complex_number_class.cpp
}

Complex::Complex(double real, double imaginary) : real(real), imaginary(imaginary) {
    // TODO: Auto-generated constructor stub
    // Complex c2(2, 3); in complex_number_class.cpp
}

Complex::Complex(const Complex &other) {
    // Complex c3 = c2; in complex_number_class.cpp
    cout << "Copy contructor !!!" << endl;
    real = other.real;
    imaginary = other.imaginary;
}

const Complex &Complex::operator=(const Complex &other) {
    // If the copy constructor is implemented, the assignment operator shall be implemented as well.
    // This method "const Complex &Complex::operator=(const Complex &other)" itself is not const,
    // because it does have to have the its value, real and imaginary.
    // c1 = c2; in complex_number_class.cpp
    cout << "Assignment operator !!!" << endl;
    real = other.real;
    imaginary = other.imaginary;

    return *this;
}

bool Complex::operator==(const Complex &other) const {
    // Overload equal to operator.
    // There is only one explicit argument instead of two. The first implicit argument is "this". It
    // does not change the actual object that it is called on, so "const" is put at the end.
    return real == other.real && imaginary == other.imaginary;
}
bool Complex::operator!=(const Complex &other) const {
    // Overload not equal to operator.
    return !(*this == other);
}

Complex Complex::operator*() const {
    // Implement the conjugate of a complex number for the fun sake.
    // "Complex operator*": It returns a brand new object. It does not change the object that it is
    // applied to. Thus, it is not a reference.
    return Complex(real, -imaginary);
}

} // namespace caveofprogramming
