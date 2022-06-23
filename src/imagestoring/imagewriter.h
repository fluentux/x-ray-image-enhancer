#ifndef IMAGESTORING_IMAGEWRITER_H
#define IMAGESTORING_IMAGEWRITER_H

#include <string>
#include "xrayimage.h"

class ImageWriter {
public:
    ImageWriter()
    {

    }

    bool write(std::string url, XrayImage<uint16_t>);
};

#endif // IMAGESTORING_IMAGEWRITER_H
