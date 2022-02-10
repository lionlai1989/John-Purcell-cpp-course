#include "FractalCreator.h"
#include <assert.h>
#include <iostream>

using namespace std;

namespace caveofprogramming {

void FractalCreator::addRange(double rangeEnd, const RGB &rgb) {
    m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    m_colors.push_back(rgb);

    if (m_bGotFirstRange) {
        m_rangeTotals.push_back(0);
    }

    m_bGotFirstRange = true;
}

int FractalCreator::getRange(int iterations) const {
    // "const" means that getRange do not modify any member variables of the FractalCreator object.

    int range = 0;

    for (int i = 1; i < m_ranges.size(); i++) { // i starts from 1.
        range = i;

        if (m_ranges[i] > iterations) {
            break;
        }
    }

    range--; // It needs to subtract 1 bcs we use 1-based index. i starts from 1.

    assert(range > -1); // assert only works in debug mode?
    assert(range < m_ranges.size());

    return range;
}

void FractalCreator::addZoom(const Zoom &zoom) {
    m_zoomList.add(zoom);
}

void FractalCreator::run(string name) {
    calculateIteration();
    calculateTotalIterations();
    calculateRangeTotals();
    drawFractal();
    writeBitmap(name);
}

FractalCreator::FractalCreator(int width, int height) : m_width(width),
                                                        m_height(height),
                                                        // For each iteration 0-MAX_ITERATIONS, check how many pixels belong to.
                                                        m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
                                                        // For every pixels, store the number of iterations of it. We want to use info of iterations to
                                                        // color our m_fractal. Instead of 2D array, using 1D array is pretty genious, but it is also more
                                                        // difficult to comprehend.
                                                        m_fractal(new int[m_width * m_height]{0}),
                                                        m_bitmap(m_width, m_height),
                                                        m_zoomList(m_width, m_height) {
    m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

FractalCreator::~FractalCreator() {
}

void FractalCreator::calculateIteration() {
    /**
     * Store the information that we need into m_fractal array.
     */
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            pair<double, double> coords = m_zoomList.doZoom(x, y);

            int iterations = Mandelbrot::getIterations(coords.first,
                                                       coords.second);

            m_fractal[y * m_width + x] = iterations;

            // When iterations==MAX_ITERATIONS, it will skew out m_histogram result. The hist. result
            // should decrease gradually.
            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                m_histogram[iterations]++;
            }
        }
    }
}

void FractalCreator::calculateRangeTotals() {
    int rangeIndex = 0;

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        int pixels = m_histogram[i];

        if (i >= m_ranges[rangeIndex + 1]) {
            rangeIndex++;
        }

        m_rangeTotals[rangeIndex] += pixels;
    }

    int overallTotal = 0;
    for (int value : m_rangeTotals) {
        cout << "Range total: " << value << endl;
        overallTotal += value;
    }
    cout << "Overall total: " << overallTotal << endl;
    cout << "Overall total value should match Total count value above." << endl;
}

void FractalCreator::calculateTotalIterations() {
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        m_total += m_histogram[i];
    }
    cout << "Total Count: " << m_total
         << ". The hist. of MAX_ITERATIONS is excluded. The total number of pixels "
         << m_width * m_height << endl;
    /**
     * Output: 15935 14640 97831 64582 39846 ... to 0. The m_histogram decreases gradually.
     */
}

void FractalCreator::drawFractal() {
    /**
     * Draw the image based on the fractal array.
     */
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            int iterations = m_fractal[y * m_width + x];

            int range = getRange(iterations);
            int rangeTotal = m_rangeTotals[range];
            int rangeStart = m_ranges[range];

            RGB &startColor = m_colors[range];
            RGB &endColor = m_colors[range + 1];
            RGB colorDiff = endColor - startColor;

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                int totalPixels = 0;

                for (int i = rangeStart; i <= iterations; i++) {
                    totalPixels += m_histogram[i];
                }

                red = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
                green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
                blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;

                /**
                 * This block of code is not needed anymore bcs a different method is used above.
                 * // When iterations == Mandelbrot::MAX_ITERATIONS, the pixel is black.
                 * double hue = 0.0; // 0 <= hue <= 1.
                 * for (int i = 0; i <= iterations; i++) {
                 *     // hue becomes bigger when the count NO. of hist. is larger.
                 *     hue += ((double)m_histogram[i]) / m_total;
                 * }
                 * red = startColor.r + colorDiff.r * hue;
                 * green = startColor.g + colorDiff.g * hue;
                 * blue = startColor.b + colorDiff.b * hue;
                 */
            }

            m_bitmap.setPixel(x, y, red, green, blue);
            /**
             * This block of code is not needed anymore bcs we have a better rendering method.
             * // 0 <= color <= 255.
             * uint8_t color = uint8_t(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);
             * // Make color change more rapidly. color is still between 0-255 bcs color is uint8_t.
             * color = color * color * color;
             * m_bitmap.setPixel(x, y, 0, color, 0);
             * if (color < min)
             *     min = color;
             * if (color > max)
             *     max = color;
             */
        }
    }
}

void FractalCreator::writeBitmap(string name) {
    m_bitmap.write(name);
}

} // namespace caveofprogramming
