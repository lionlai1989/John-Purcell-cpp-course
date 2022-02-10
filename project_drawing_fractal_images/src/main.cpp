#include "FractalCreator.h"
#include <iostream>

using namespace std;
using namespace caveofprogramming;

int main(int argc, char *argv[]) {
    /*
     * TODO: 
     * 1. Make this code run faster.
     * 2. Use SDL (Simple DirectMedia Layer) library in beginner's course to click on a spot and
     *    redraw this fractal image.
     * 3. Use valgrind to check your program for memory leaks and things like overwriting the end of
     *    an array. If you do write into memory you've not allocated or you read memory that you've
     *    not allocated then you could end up with your program intermittently crashing which is
     *    really horrible.
     */
    FractalCreator fractalCreator(800, 600);

    fractalCreator.addRange(0.0, RGB(0, 0, 0));
    fractalCreator.addRange(0.3, RGB(255, 0, 0));
    fractalCreator.addRange(0.7, RGB(255, 255, 0));
    fractalCreator.addRange(1.0, RGB(255, 255, 255));

    fractalCreator.addZoom(Zoom(295, 202, 0.1));
    fractalCreator.addZoom(Zoom(312, 304, 0.1));

    fractalCreator.run("test.bmp");
    cout << "Finished." << endl;
    return 0;
}
