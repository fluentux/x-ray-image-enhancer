#ifndef IMAGESTORING_IMAGEREADER_H
#define IMAGESTORING_IMAGEREADER_H

#include <string>
#include "xrayimage.h"

class ImageReader {
public:
    ImageReader();

    XrayImage<uint8_t> read(std::string url);
};

#endif // IMAGESTORING_IMAGEREADER_H
