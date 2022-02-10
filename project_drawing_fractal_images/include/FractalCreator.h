#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"
#include "Zoom.h"
#include "ZoomList.h"
#include <cstdint>
#include <math.h>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace caveofprogramming {

// TODO: Add methods to check if the value of ranges make sense.
class FractalCreator {
  private:
    int m_width;
    int m_height;
    unique_ptr<int[]> m_histogram;
    unique_ptr<int[]> m_fractal;
    Bitmap m_bitmap;
    ZoomList m_zoomList;
    int m_total{0};

    vector<int> m_ranges;
    vector<RGB> m_colors;
    vector<int> m_rangeTotals;

    bool m_bGotFirstRange{false};

  private:
    void calculateIteration();
    void calculateTotalIterations();
    void calculateRangeTotals();
    void drawFractal();
    void writeBitmap(string name);
    int getRange(int iterations) const;

  public:
    FractalCreator(int width, int height);
    virtual ~FractalCreator();
    void run(string name);
    void addZoom(const Zoom &zoom);
    void addRange(double rangeEnd, const RGB &rgb);
};

} // namespace caveofprogramming

#endif
