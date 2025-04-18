#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace caveofprogramming {

Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height), m_pPixels(new uint8_t[width * height * 3]{}) {
    // Use "new" to allocate memory because the size of the bitmap is only known at the run time.
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    // Get a primitive pointer from a unique_ptr object. pPixel points to the start of the array.
    uint8_t *pPixel = m_pPixels.get();

    pPixel += (y * 3) * m_width + (x * 3); // Each pixel has 3 bytes.
    /**
     * Bitmap is little-endian file format.
     */
    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red;
}

bool Bitmap::write(string filename) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width * m_height * 3;
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    ofstream file;
    file.open(filename, ios::out | ios::binary);
    if (!file) {
        return false;
    }
    file.write((char *)&fileHeader, sizeof(fileHeader));
    file.write((char *)&infoHeader, sizeof(infoHeader));
    file.write((char *)(m_pPixels.get()), m_width * m_height * 3); // Get a primitive pointer from a unique_ptr object.
    file.close();
    if (!file) {
        return false;
    }

    return true;
}

Bitmap::~Bitmap() {
}

} // namespace caveofprogramming
