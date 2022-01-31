#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>
using namespace std;

namespace caveofprogramming {

/**
 * Use pack(push) and pack(pop) to ensure that only our struct is padded by 2 bytes. If pack(pop) is
 * not used here, there will be the following error.
 * *** stack smashing detected ***: terminated
 * Aborted (core dumped)
 * https://stackoverflow.com/questions/58197050/pragma-packpush-without-corresponding-pop-leads-to-stack-smashing 
 */
#pragma pack(push)
#pragma pack(2)
struct BitmapInfoHeader {
    int32_t headerSize{40}; // There are 40 bytes in BitmapInfoHeader.
    int32_t width;
    int32_t height;
    int16_t planes{1};
    int16_t bitsPerPixel{24}; // 3 x 8-bits = 24
    int32_t compression{0};
    int32_t dataSize{0};
    int32_t horizontalResolution{2400};
    int32_t verticalResolution{2400};
    int32_t colors{0};
    int32_t importantColors{0};
};
#pragma pack(pop)

} // namespace caveofprogramming

#endif
