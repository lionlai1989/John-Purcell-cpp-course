#ifndef ZOOM_H_
#define ZOOM_H_

namespace caveofprogramming {

struct Zoom {
    // struct has all members public by default.
    // class has all members private by default.
    // Except from that, struct and class are exactly the same technically.
    int x{0};
    int y{0};
    double scale{0.0};
    Zoom(int x, int y, double scale) : x(x), y(y), scale(scale){/*Dummy code*/};
};

} // namespace caveofprogramming

#endif
