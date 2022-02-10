#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <cstdint>
#include <memory>
#include <string>

using namespace std;

namespace caveofprogramming {

class Mandelbrot {
  public:
    static const int MAX_ITERATIONS = 1000;

  public:
    Mandelbrot();
    static int getIterations(double x, double y);
    virtual ~Mandelbrot();
};

} // namespace caveofprogramming

#endif
