#include "Bitmap.h"

namespace caveofprogramming {

Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height) {
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
}

bool Bitmap::write(string filename) {
    return false;
}

Bitmap::~Bitmap() {
}

} // namespace caveofprogramming
