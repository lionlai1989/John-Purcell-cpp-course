#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Zoom.h"
#include <cstdint>
#include <iostream>
#include <math.h>
#include <memory>

using namespace std;
using namespace caveofprogramming;

int main(int argc, char *argv[]) {
    int const WIDTH = 800, HEIGHT = 600;
    Bitmap bitmap(WIDTH, HEIGHT);

    double min = 999999999;
    double max = -999999999;

    // For each iteration 0-MAX_ITERATIONS, check how many pixels belong to.
    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
    // For every pixels, store the number of iterations of it. We want to use info of iterations to
    // color our fractal. Instead of 2D array, using 1D array is pretty genious, but it is also more
    // difficult to comprehend.
    unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{0});

    /**
     * Store the information that we need into fractal array.
     */
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT; // Plot the whole set.
            double yFractal = (y - HEIGHT / 2 - 0) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIteration(xFractal, yFractal);

            fractal[y * WIDTH + x] = iterations;

            // When iterations==MAX_ITERATIONS, it will skew out histogram result. The hist. result
            // should decrease gradually.
            if (iterations < Mandelbrot::MAX_ITERATIONS) {
                histogram[iterations]++;
            }
        }
    }

    cout << endl;
    int count = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        cout << histogram[i] << " " << flush;
        count += histogram[i];
    }
    cout << endl;
    cout << "Count " << count << ". The hist. of MAX_ITERATIONS is excluded. The total number of pixels " << WIDTH * HEIGHT << endl;
    cout << endl;
    /**
     * Output: 15935 14640 97831 64582 39846 ... to 0. The histogram decreases gradually.
     */

    cout << "min: " << min << ", max: " << max << endl; // Output: min: 0, max: 253

    int total = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        total += histogram[i];
    }
    /**
     * Draw the image based on the fractal array.
     */
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iterations = fractal[y * WIDTH + x];
            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                // When iterations == Mandelbrot::MAX_ITERATIONS, the pixel is black.
                double hue = 0; // 0 <= hue <= 1.
                for (int i = 0; i <= iterations; i++) {
                    // hue becomes bigger when the count NO. of hist. is larger.
                    hue += ((double)histogram[i]) / total;
                }
                green = pow(255, hue);
            }
            bitmap.setPixel(x, y, red, green, blue);

            /**
             * This block of code is not needed anymore bcs we have a better rendering method.
             * // 0 <= color <= 255.
             * uint8_t color = uint8_t(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);
             * // Make color change more rapidly. color is still between 0-255 bcs color is uint8_t.
             * color = color * color * color;
             * bitmap.setPixel(x, y, 0, color, 0);
             * if (color < min)
             *     min = color;
             * if (color > max)
             *     max = color;
             */
        }
    }

    bitmap.write("test.bmp");
    cout << "Finished." << endl;
    return 0;
}
