#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint> // c standard int
using namespace std;

/**
 * In C/C++, if we have a struct like below, it will align data with padding in a way that's most
 * efficient and we can't allow that here, because we want to write "BitmapFileHeader" literally to
 * a file. We need to tell C/C++ to pack the data in the way that it looks exactly like this.
 * "#pragma pack(2)" makes C++ align all of the data in "BitmapFileHeader" on two bytes boundaries.
 * Two bytes boundaries rather than putting extra padding in to align all this in what it considers
 * the most efficient way possible. 
 * The bottom line is this struct will be kept in memory exactly as it looks here. There will be no
 * hidden padding in there. And if we don't do that then our final bitmap will be unreadable. There
 * will be extra padding bytes behind the scenes within this struct.
 */
#pragma pack(2)

/**
 * One of the differences between a struct and a class is that members of a struct are public by
 * default and members of a class are private by default. We want to access the members directly 
 * here for efficiency and this will not have any methods so it's better if we use struct here, or
 * we could just as well use a class and just put public at the top. 
 */
namespace caveofprogramming {

struct BitmapFileHeader {
    char header[2] = {'B', 'M'}; // It means BitMap.
    /**
     * int fileSize; "int" cannot make sure it's 32-bits integer, but "int32_t" can.
     * Think about CODE PORTABILITY.
     */
    int32_t fileSize;
    int32_t reserved = {0};
    int32_t dataOffset;
};

} // namespace caveofprogramming
#endif
